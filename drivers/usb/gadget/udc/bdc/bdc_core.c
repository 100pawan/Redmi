/*
 * bdc_core.c - BRCM BDC USB3.0 device controller core operations
 *
 * Copyright (C) 2014 Broadcom Corporation
 *
 * Author: Ashwini Pahuja
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/list.h>
#include <linux/delay.h>
#include <linux/dma-mapping.h>
#include <linux/dmapool.h>
#include <linux/of.h>
#include <linux/moduleparam.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>

#include "bdc.h"
#include "bdc_dbg.h"

/* Poll till controller status is not OIP */
static int poll_oip(struct bdc *bdc, int usec)
{
	u32 status;
	/* Poll till STS!= OIP */
	while (usec) {
		status = bdc_readl(bdc->regs, BDC_BDCSC);
		if (BDC_CSTS(status) != BDC_OIP) {
			dev_dbg(bdc->dev,
				"poll_oip complete status=%d",
				BDC_CSTS(status));
			return 0;
		}
		udelay(10);
		usec -= 10;
	}
	dev_err(bdc->dev, "Err: operation timedout BDCSC: 0x%08x\n", status);

	return -ETIMEDOUT;
}

/* Stop the BDC controller */
int bdc_stop(struct bdc *bdc)
{
	int ret;
	u32 temp;

	dev_dbg(bdc->dev, "%s ()\n\n", __func__);
	temp = bdc_readl(bdc->regs, BDC_BDCSC);
	/* Check if BDC is already halted */
	if (BDC_CSTS(temp) == BDC_HLT) {
		dev_vdbg(bdc->dev, "BDC already halted\n");
		return 0;
	}
	temp &= ~BDC_COP_MASK;
	temp |= BDC_COS|BDC_COP_STP;
	bdc_writel(bdc->regs, BDC_BDCSC, temp);

	ret = poll_oip(bdc, BDC_COP_TIMEOUT);
	if (ret)
		dev_err(bdc->dev, "bdc stop operation failed");

	return ret;
}

/* Issue a reset to BDC controller */
int bdc_reset(struct bdc *bdc)
{
	u32 temp;
	int ret;

	dev_dbg(bdc->dev, "%s ()\n", __func__);
	/* First halt the controller */
	ret = bdc_stop(bdc);
	if (ret)
		return ret;

	temp = bdc_readl(bdc->regs, BDC_BDCSC);
	temp &= ~BDC_COP_MASK;
	temp |= BDC_COS|BDC_COP_RST;
	bdc_writel(bdc->regs, BDC_BDCSC, temp);
	ret = poll_oip(bdc, BDC_COP_TIMEOUT);
	if (ret)
		dev_err(bdc->dev, "bdc reset operation failed");

	return ret;
}

/* Run the BDC controller */
int bdc_run(struct bdc *bdc)
{
	u32 temp;
	int ret;

	dev_dbg(bdc->dev, "%s ()\n", __func__);
	temp = bdc_readl(bdc->regs, BDC_BDCSC);
	/* if BDC is already in running state then do not do anything */
	if (BDC_CSTS(temp) == BDC_NOR) {
		dev_warn(bdc->dev, "bdc is already in running state\n");
		return 0;
	}
	temp &= ~BDC_COP_MASK;
	temp |= BDC_COP_RUN;
	temp |= BDC_COS;
	bdc_writel(bdc->regs, BDC_BDCSC, temp);
	ret = poll_oip(bdc, BDC_COP_TIMEOUT);
	if (ret) {
		dev_err(bdc->dev, "bdc run operation failed:%d", ret);
		return ret;
	}
	temp = bdc_readl(bdc->regs, BDC_BDCSC);
	if (BDC_CSTS(temp) != BDC_NOR) {
		dev_err(bdc->dev, "bdc not in normal mode after RUN op :%d\n",
								BDC_CSTS(temp));
		return -ESHUTDOWN;
	}

	return 0;
}

/*
 * Present the termination to the host, typically called from upstream port
 * event with Vbus present =1
 */
void bdc_softconn(struct bdc *bdc)
{
	u32 uspc;

	uspc = bdc_readl(bdc->regs, BDC_USPC);
	uspc &= ~BDC_PST_MASK;
	uspc |= BDC_LINK_STATE_RX_DET;
	uspc |= BDC_SWS;
	dev_dbg(bdc->dev, "%s () uspc=%08x\n", __func__, uspc);
	bdc_writel(bdc->regs, BDC_USPC, uspc);
}

/* Remove the termination */
void bdc_softdisconn(struct bdc *bdc)
{
	u32 uspc;

	uspc = bdc_readl(bdc->regs, BDC_USPC);
	uspc |= BDC_SDC;
	uspc &= ~BDC_SCN;
	dev_dbg(bdc->dev, "%s () uspc=%x\n", __func__, uspc);
	bdc_writel(bdc->regs, BDC_USPC, uspc);
}

/* Set up the scratchpad buffer array and scratchpad buffers, if needed. */
static int scratchpad_setup(struct bdc *bdc)
{
	int sp_buff_size;
	u32 low32;
	u32 upp32;

	sp_buff_size = BDC_SPB(bdc_readl(bdc->regs, BDC_BDCCFG0));
	dev_dbg(bdc->dev, "%s() sp_buff_size=%d\n", __func__, sp_buff_size);
	if (!sp_buff_size) {
		dev_dbg(bdc->dev, "Scratchpad buffer not needed\n");
		return 0;
	}
	/* Refer to BDC spec, Table 4 for description of SPB */
	sp_buff_size = 1 << (sp_buff_size + 5);
	dev_dbg(bdc->dev, "Allocating %d bytes for scratchpad\n", sp_buff_size);
	bdc->scratchpad.buff  =  dma_zalloc_coherent(bdc->dev, sp_buff_size,
					&bdc->scratchpad.sp_dma, GFP_KERNEL);

	if (!bdc->scratchpad.buff)
		goto fail;

	bdc->sp_buff_size = sp_buff_size;
	bdc->scratchpad.size = sp_buff_size;
	low32 = lower_32_bits(bdc->scratchpad.sp_dma);
	upp32 = upper_32_bits(bdc->scratchpad.sp_dma);
	cpu_to_le32s(&low32);
	cpu_to_le32s(&upp32);
	bdc_writel(bdc->regs, BDC_SPBBAL, low32);
	bdc_writel(bdc->regs, BDC_SPBBAH, upp32);
	return 0;

fail:
	bdc->scratchpad.buff = NULL;

	return -ENOMEM;
}

/* Allocate the status report ring */
static int setup_srr(struct bdc *bdc, int interrupter)
{
	dev_dbg(bdc->dev, "%s() NUM_SR_ENTRIES:%d\n", __func__, NUM_SR_ENTRIES);
	/* Reset the SRR */
	bdc_writel(bdc->regs, BDC_SRRINT(0), BDC_SRR_RWS | BDC_SRR_RST);
	bdc->srr.dqp_index = 0;
	/* allocate the status report descriptors */
	bdc->srr.sr_bds = dma_zalloc_coherent(
					bdc->dev,
					NUM_SR_ENTRIES * sizeof(struct bdc_bd),
					&bdc->srr.dma_addr,
					GFP_KERNEL);
	if (!bdc->srr.sr_bds)
		return -ENOMEM;

	return 0;
}

/* Initialize the HW regs and internal data structures */
static void bdc_mem_init(struct bdc *bdc, bool reinit)
{
	u8 size = 0;
	u32 usb2_pm;
	u32 low32;
	u32 upp32;
	u32 temp;

	dev_dbg(bdc->dev, "%s ()\n", __func__);
	bdc->ep0_state = WAIT_FOR_SETUP;
	bdc->dev_addr = 0;
	bdc->srr.eqp_index = 0;
	bdc->srr.dqp_index = 0;
	bdc->zlp_needed = false;
	bdc->delayed_status = false;

	bdc_writel(bdc->regs, BDC_SPBBAL, bdc->scratchpad.sp_dma);
	/* Init the SRR */
	temp = BDC_SRR_RWS | BDC_SRR_RST;
	/* Reset the SRR */
	bdc_writel(bdc->regs, BDC_SRRINT(0), temp);
	dev_dbg(bdc->dev, "bdc->srr.sr_bds =%p\n", bdc->srr.sr_bds);
	temp = lower_32_bits(bdc->srr.dma_addr);
	size = fls(NUM_SR_ENTRIES) - 2;
	temp |= size;
	dev_dbg(bdc->dev, "SRRBAL[0]=%08x NUM_SR_ENTRIES:%d size:%d\n",
						temp, NUM_SR_ENTRIES, size);

	low32 = lower_32_bits(temp);
	upp32 = upper_32_bits(bdc->srr.dma_addr);
	cpu_to_le32s(&low32);
	cpu_to_le32s(&upp32);

	/* Write the dma addresses into regs*/
	bdc_writel(bdc->regs, BDC_SRRBAL(0), low32);
	bdc_writel(bdc->regs, BDC_SRRBAH(0), upp32);

	temp = bdc_readl(bdc->regs, BDC_SRRINT(0));
	temp |= BDC_SRR_IE;
	temp &= ~(BDC_SRR_RST | BDC_SRR_RWS);
	bdc_writel(bdc->regs, BDC_SRRINT(0), temp);

	/* Set the Interrupt Coalescence ~500 usec */
	temp = bdc_readl(bdc->regs, BDC_INTCTLS(0));
	temp &= ~0xffff;
	temp |= INT_CLS;
	bdc_writel(bdc->regs, BDC_INTCTLS(0), temp);

	usb2_pm = bdc_readl(bdc->regs, BDC_USPPM2);
	dev_dbg(bdc->dev, "usb2_pm=%08x", usb2_pm);
	/* Enable hardware LPM Enable */
	usb2_pm |= BDC_HLE;
	bdc_writel(bdc->regs, BDC_USPPM2, usb2_pm);

	/* readback for debug */
	usb2_pm = bdc_readl(bdc->regs, BDC_USPPM2);
	dev_dbg(bdc->dev, "usb2_pm=%08x\n", usb2_pm);

	/* Disable any unwanted SR's on SRR */
	temp = bdc_readl(bdc->regs, BDC_BDCSC);
	/* We don't want Microframe counter wrap SR */
	temp |= BDC_MASK_MCW;
	bdc_writel(bdc->regs, BDC_BDCSC, temp);

	/*
	 * In some error cases, driver has to reset the entire BDC controller
	 * in that case reinit is passed as 1
	 */
	if (reinit) {
<<<<<<< HEAD
		int i;
=======
>>>>>>> FETCH_HEAD
		/* Enable interrupts */
		temp = bdc_readl(bdc->regs, BDC_BDCSC);
		temp |= BDC_GIE;
		bdc_writel(bdc->regs, BDC_BDCSC, temp);
		/* Init scratchpad to 0 */
		memset(bdc->scratchpad.buff, 0, bdc->sp_buff_size);
		/* Initialize SRR to 0 */
		memset(bdc->srr.sr_bds, 0,
					NUM_SR_ENTRIES * sizeof(struct bdc_bd));
<<<<<<< HEAD
		/* clear ep flags to avoid post disconnect stops/deconfigs */
		for (i = 1; i < bdc->num_eps; ++i)
			bdc->bdc_ep_array[i]->flags = 0;
=======
>>>>>>> FETCH_HEAD
	} else {
		/* One time initiaization only */
		/* Enable status report function pointers */
		bdc->sr_handler[0] = bdc_sr_xsf;
		bdc->sr_handler[1] = bdc_sr_uspc;

		/* EP0 status report function pointers */
		bdc->sr_xsf_ep0[0] = bdc_xsf_ep0_setup_recv;
		bdc->sr_xsf_ep0[1] = bdc_xsf_ep0_data_start;
		bdc->sr_xsf_ep0[2] = bdc_xsf_ep0_status_start;
	}
}

/* Free the dynamic memory */
static void bdc_mem_free(struct bdc *bdc)
{
	dev_dbg(bdc->dev, "%s\n", __func__);
	/* Free SRR */
	if (bdc->srr.sr_bds)
		dma_free_coherent(bdc->dev,
					NUM_SR_ENTRIES * sizeof(struct bdc_bd),
					bdc->srr.sr_bds, bdc->srr.dma_addr);

	/* Free scratchpad */
	if (bdc->scratchpad.buff)
		dma_free_coherent(bdc->dev, bdc->sp_buff_size,
				bdc->scratchpad.buff, bdc->scratchpad.sp_dma);

	/* Destroy the dma pools */
	dma_pool_destroy(bdc->bd_table_pool);

	/* Free the bdc_ep array */
	kfree(bdc->bdc_ep_array);

	bdc->srr.sr_bds = NULL;
	bdc->scratchpad.buff = NULL;
	bdc->bd_table_pool = NULL;
	bdc->bdc_ep_array = NULL;
}

/*
 * bdc reinit gives a controller reset and reinitialize the registers,
 * called from disconnect/bus reset scenario's, to ensure proper HW cleanup
 */
int bdc_reinit(struct bdc *bdc)
{
	int ret;

	dev_dbg(bdc->dev, "%s\n", __func__);
	ret = bdc_stop(bdc);
	if (ret)
		goto out;

	ret = bdc_reset(bdc);
	if (ret)
		goto out;

	/* the reinit flag is 1 */
	bdc_mem_init(bdc, true);
	ret = bdc_run(bdc);
out:
	bdc->reinit = false;

	return ret;
}

/* Allocate all the dyanmic memory */
static int bdc_mem_alloc(struct bdc *bdc)
{
	u32 page_size;
	unsigned int num_ieps, num_oeps;

	dev_dbg(bdc->dev,
		"%s() NUM_BDS_PER_TABLE:%d\n", __func__,
		NUM_BDS_PER_TABLE);
	page_size = BDC_PGS(bdc_readl(bdc->regs, BDC_BDCCFG0));
	/* page size is 2^pgs KB */
	page_size = 1 << page_size;
	/* KB */
	page_size <<= 10;
	dev_dbg(bdc->dev, "page_size=%d\n", page_size);

	/* Create a pool of bd tables */
	bdc->bd_table_pool =
	    dma_pool_create("BDC BD tables", bdc->dev, NUM_BDS_PER_TABLE * 16,
								16, page_size);

	if (!bdc->bd_table_pool)
		goto fail;

	if (scratchpad_setup(bdc))
		goto fail;

	/* read from regs */
	num_ieps = NUM_NCS(bdc_readl(bdc->regs, BDC_FSCNIC));
	num_oeps = NUM_NCS(bdc_readl(bdc->regs, BDC_FSCNOC));
	/* +2: 1 for ep0 and the other is rsvd i.e. bdc_ep[0] is rsvd */
	bdc->num_eps = num_ieps + num_oeps + 2;
	dev_dbg(bdc->dev,
		"ieps:%d eops:%d num_eps:%d\n",
		num_ieps, num_oeps, bdc->num_eps);
	/* allocate array of ep pointers */
	bdc->bdc_ep_array = kcalloc(bdc->num_eps, sizeof(struct bdc_ep *),
								GFP_KERNEL);
	if (!bdc->bdc_ep_array)
		goto fail;

	dev_dbg(bdc->dev, "Allocating sr report0\n");
	if (setup_srr(bdc, 0))
		goto fail;

	return 0;
fail:
	dev_warn(bdc->dev, "Couldn't initialize memory\n");
	bdc_mem_free(bdc);

	return -ENOMEM;
}

/* opposite to bdc_hw_init */
static void bdc_hw_exit(struct bdc *bdc)
{
	dev_dbg(bdc->dev, "%s ()\n", __func__);
	bdc_mem_free(bdc);
}

/* Initialize the bdc HW and memory */
static int bdc_hw_init(struct bdc *bdc)
{
	int ret;

	dev_dbg(bdc->dev, "%s ()\n", __func__);
	ret = bdc_reset(bdc);
	if (ret) {
		dev_err(bdc->dev, "err resetting bdc abort bdc init%d\n", ret);
		return ret;
	}
	ret = bdc_mem_alloc(bdc);
	if (ret) {
		dev_err(bdc->dev, "Mem alloc failed, aborting\n");
		return -ENOMEM;
	}
	bdc_mem_init(bdc, 0);
	bdc_dbg_regs(bdc);
	dev_dbg(bdc->dev, "HW Init done\n");

	return 0;
}

static int bdc_probe(struct platform_device *pdev)
{
	struct bdc *bdc;
	struct resource *res;
	int ret = -ENOMEM;
	int irq;
	u32 temp;
	struct device *dev = &pdev->dev;

	dev_dbg(dev, "%s()\n", __func__);
	bdc = devm_kzalloc(dev, sizeof(*bdc), GFP_KERNEL);
	if (!bdc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	bdc->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(bdc->regs)) {
		dev_err(dev, "ioremap error\n");
		return -ENOMEM;
	}
	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(dev, "platform_get_irq failed:%d\n", irq);
		return irq;
	}
	spin_lock_init(&bdc->lock);
	platform_set_drvdata(pdev, bdc);
	bdc->irq = irq;
	bdc->dev = dev;
	dev_dbg(bdc->dev, "bdc->regs: %p irq=%d\n", bdc->regs, bdc->irq);

	temp = bdc_readl(bdc->regs, BDC_BDCCAP1);
	if ((temp & BDC_P64) &&
			!dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64))) {
		dev_dbg(bdc->dev, "Using 64-bit address\n");
	} else {
		ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		if (ret) {
			dev_err(bdc->dev, "No suitable DMA config available, abort\n");
			return -ENOTSUPP;
		}
		dev_dbg(bdc->dev, "Using 32-bit address\n");
	}
	ret = bdc_hw_init(bdc);
	if (ret) {
		dev_err(bdc->dev, "BDC init failure:%d\n", ret);
		return ret;
	}
	ret = bdc_udc_init(bdc);
	if (ret) {
		dev_err(bdc->dev, "BDC Gadget init failure:%d\n", ret);
		goto cleanup;
	}
	return 0;

cleanup:
	bdc_hw_exit(bdc);

	return ret;
}

static int bdc_remove(struct platform_device *pdev)
{
	struct bdc *bdc;

	bdc  = platform_get_drvdata(pdev);
	dev_dbg(bdc->dev, "%s ()\n", __func__);
	bdc_udc_exit(bdc);
	bdc_hw_exit(bdc);

	return 0;
}

static struct platform_driver bdc_driver = {
	.driver		= {
		.name	= BRCM_BDC_NAME,
	},
	.probe		= bdc_probe,
	.remove		= bdc_remove,
};

module_platform_driver(bdc_driver);
MODULE_AUTHOR("Ashwini Pahuja <ashwini.linux@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION(BRCM_BDC_DESC);
