/**
 * ulpi.c - DesignWare USB3 Controller's ULPI PHY interface
 *
 * Copyright (C) 2015 Intel Corporation
 *
 * Author: Heikki Krogerus <heikki.krogerus@linux.intel.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

<<<<<<< HEAD
#include <linux/delay.h>
#include <linux/time64.h>
=======
>>>>>>> FETCH_HEAD
#include <linux/ulpi/regs.h>

#include "core.h"
#include "io.h"

#define DWC3_ULPI_ADDR(a) \
		((a >= ULPI_EXT_VENDOR_SPECIFIC) ? \
		DWC3_GUSB2PHYACC_ADDR(ULPI_ACCESS_EXTENDED) | \
		DWC3_GUSB2PHYACC_EXTEND_ADDR(a) : DWC3_GUSB2PHYACC_ADDR(a))

<<<<<<< HEAD
#define DWC3_ULPI_BASE_DELAY	DIV_ROUND_UP(NSEC_PER_SEC, 60000000L)

static int dwc3_ulpi_busyloop(struct dwc3 *dwc, u8 addr, bool read)
{
	unsigned long ns = 5L * DWC3_ULPI_BASE_DELAY;
	unsigned int count = 1000;
	u32 reg;

	if (addr >= ULPI_EXT_VENDOR_SPECIFIC)
		ns += DWC3_ULPI_BASE_DELAY;

	if (read)
		ns += DWC3_ULPI_BASE_DELAY;

	while (count--) {
		ndelay(ns);
=======
static int dwc3_ulpi_busyloop(struct dwc3 *dwc)
{
	unsigned count = 1000;
	u32 reg;

	while (count--) {
>>>>>>> FETCH_HEAD
		reg = dwc3_readl(dwc->regs, DWC3_GUSB2PHYACC(0));
		if (!(reg & DWC3_GUSB2PHYACC_BUSY))
			return 0;
		cpu_relax();
	}

	return -ETIMEDOUT;
}

static int dwc3_ulpi_read(struct device *dev, u8 addr)
{
	struct dwc3 *dwc = dev_get_drvdata(dev);
	u32 reg;
	int ret;

	reg = DWC3_GUSB2PHYACC_NEWREGREQ | DWC3_ULPI_ADDR(addr);
	dwc3_writel(dwc->regs, DWC3_GUSB2PHYACC(0), reg);

<<<<<<< HEAD
	ret = dwc3_ulpi_busyloop(dwc, addr, true);
=======
	ret = dwc3_ulpi_busyloop(dwc);
>>>>>>> FETCH_HEAD
	if (ret)
		return ret;

	reg = dwc3_readl(dwc->regs, DWC3_GUSB2PHYACC(0));

	return DWC3_GUSB2PHYACC_DATA(reg);
}

static int dwc3_ulpi_write(struct device *dev, u8 addr, u8 val)
{
	struct dwc3 *dwc = dev_get_drvdata(dev);
	u32 reg;

	reg = DWC3_GUSB2PHYACC_NEWREGREQ | DWC3_ULPI_ADDR(addr);
	reg |= DWC3_GUSB2PHYACC_WRITE | val;
	dwc3_writel(dwc->regs, DWC3_GUSB2PHYACC(0), reg);

<<<<<<< HEAD
	return dwc3_ulpi_busyloop(dwc, addr, false);
=======
	return dwc3_ulpi_busyloop(dwc);
>>>>>>> FETCH_HEAD
}

static const struct ulpi_ops dwc3_ulpi_ops = {
	.read = dwc3_ulpi_read,
	.write = dwc3_ulpi_write,
};

int dwc3_ulpi_init(struct dwc3 *dwc)
{
	/* Register the interface */
	dwc->ulpi = ulpi_register_interface(dwc->dev, &dwc3_ulpi_ops);
	if (IS_ERR(dwc->ulpi)) {
		dev_err(dwc->dev, "failed to register ULPI interface");
		return PTR_ERR(dwc->ulpi);
	}

	return 0;
}

void dwc3_ulpi_exit(struct dwc3 *dwc)
{
	if (dwc->ulpi) {
		ulpi_unregister_interface(dwc->ulpi);
		dwc->ulpi = NULL;
	}
}
