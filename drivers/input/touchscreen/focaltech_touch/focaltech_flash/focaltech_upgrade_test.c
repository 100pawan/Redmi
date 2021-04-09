/*
 *
 * FocalTech fts TouchScreen driver.
 *
 * Copyright (c) 2010-2017, Focaltech Ltd. All rights reserved.
<<<<<<< HEAD
 * Copyright (C) 2019 XiaoMi, Inc.
=======
>>>>>>> FETCH_HEAD
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/*****************************************************************************
<<<<<<< HEAD
*
* File Name: focaltech_upgrade_test.c
*
* Author:    fupeipei
*
* Created:    2016-08-22
*
* Abstract:
*
* Reference:
*
*****************************************************************************/

/*****************************************************************************
* 1.Included header files
*****************************************************************************/
#include "../focaltech_core.h"
#include "../focaltech_flash.h"
#include <linux/device.h>
#include <linux/pm_wakeup.h>
#include <linux/timer.h>

/*****************************************************************************
* Static variables
*****************************************************************************/
#define FTS_GET_UPGRADE_TIME                    0

/*****************************************************************************
* Global variable or extern global variabls/functions
*****************************************************************************/
struct wakeup_source ps_lock;

#define FTS_DEBUG_UPGRADE(fmt, args...) do{\
					                            printk(KERN_ERR "[FTS][UPGRADE]:##############################################################################\n");\
					                            printk(KERN_ERR "[FTS][UPGRADE]: "fmt"\n", ##args);\
					                            printk(KERN_ERR "[FTS][UPGRADE]:##############################################################################\n");\
					                       }while(0)\

/*****************************************************************************
* Static function prototypes
*****************************************************************************/
#if (FTS_UPGRADE_STRESS_TEST)
/************************************************************************
* Name: fts_ctpm_auto_upgrade_pingpong
* Brief:  0
* Input:  0
* Output: 0
* Return: 0
***********************************************************************/
=======
 *
 * File Name: focaltech_upgrade_test.c
 *
 * Author:    fupeipei
 *
 * Created:    2016-08-22
 *
 * Abstract:
 *
 * Reference:
 *
 *****************************************************************************/

/*****************************************************************************
 * 1.Included header files
 *****************************************************************************/
#include "../focaltech_core.h"
#include "../focaltech_flash.h"
#include <linux/timer.h>

/*****************************************************************************
 * Static variables
 *****************************************************************************/
#define FTS_GET_UPGRADE_TIME                    0

/*****************************************************************************
 * Global variable or extern global variabls/functions
 *****************************************************************************/

#define FTS_DEBUG_UPGRADE(fmt, args...) do {\
			pr_err("[FTS][UPGRADE]:################\n");\
			pr_err("[FTS][UPGRADE]: "fmt"\n", ##args);\
			pr_err("[FTS][UPGRADE]:################\n");\
		} while (0)\

/*****************************************************************************
 * Static function prototypes
 *****************************************************************************/
#if (FTS_UPGRADE_STRESS_TEST)
/************************************************************************
 * Name: fts_ctpm_auto_upgrade_pingpong
 * Brief:  0
 * Input:  0
 * Output: 0
 * Return: 0
 ***********************************************************************/
>>>>>>> FETCH_HEAD
static int fts_ctpm_auto_upgrade_pingpong(struct i2c_client *client)
{
	u8 uc_tp_fm_ver;
	int i_ret = 0;
	u8 uc_upgrade_times = 0;

	FTS_FUNC_ENTER();

	/* pingpong test mode, need upgrade */
	FTS_INFO("[UPGRADE]: pingpong test mode, need upgrade!!");
<<<<<<< HEAD
	do
	{
=======
	do {
>>>>>>> FETCH_HEAD
		uc_upgrade_times++;

		/* fw upgrade */
		i_ret = fts_ctpm_fw_upgrade(client);

<<<<<<< HEAD
		if (i_ret == 0) /* upgrade success */
		{
			fts_i2c_read_reg(client, FTS_REG_FW_VER, &uc_tp_fm_ver);
			FTS_DEBUG("[UPGRADE]: upgrade to new version 0x%x", uc_tp_fm_ver);
		}
		else /* upgrade fail */
		{
			/* if upgrade fail, reset to run ROM. if app in flash is ok. TP will work success */
			FTS_INFO("[UPGRADE]: upgrade fail, reset now!!");
			fts_ctpm_rom_or_pram_reset(client);
		}
	}
	while ((i_ret != 0) && (uc_upgrade_times < 2));  /* if upgrade fail, upgrade again. then return */
=======
		if (i_ret == 0) {
			/* upgrade success */
			fts_i2c_read_reg(client, FTS_REG_FW_VER, &uc_tp_fm_ver);
			FTS_DEBUG("[UPGRADE]: upgrade to new version 0x%x",
					uc_tp_fm_ver);
		} else {
			/* upgrade fail */
			/* if upgrade fail, reset to run ROM.
			 * if app in flash is ok. TP will work success
			 */
			FTS_INFO("[UPGRADE]: upgrade fail, reset now!!");
			fts_ctpm_rom_or_pram_reset(client);
		}
		/* if upgrade fail, upgrade again. then return */
	} while ((i_ret != 0) && (uc_upgrade_times < 2));
>>>>>>> FETCH_HEAD

	FTS_FUNC_EXIT();
	return i_ret;
}

/************************************************************************
<<<<<<< HEAD
* Name: fts_ctpm_auto_upgrade
* Brief:  0
* Input:  0
* Output: 0
* Return: 0
***********************************************************************/
=======
 * Name: fts_ctpm_auto_upgrade
 * Brief:  0
 * Input:  0
 * Output: 0
 * Return: 0
 ***********************************************************************/
>>>>>>> FETCH_HEAD
void fts_ctpm_display_upgrade_time(bool start_time)
{
#if FTS_GET_UPGRADE_TIME
	static struct timeval tpend;
	static struct timeval tpstart;
	static int timeuse;

<<<<<<< HEAD
	if (start_time)
	{
		do_gettimeofday(&tpstart);
	}
	else
	{
		do_gettimeofday(&tpend);
		timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+ tpend.tv_usec-tpstart.tv_usec;
		timeuse/=1000000;
		FTS_DEBUG( "[UPGRADE]: upgrade success : Use time: %d Seconds!!", timeuse);
=======
	if (start_time) {
		do_gettimeofday(&tpstart);
	} else {
		do_gettimeofday(&tpend);
		timeuse = 1000000 * (tpend.tv_sec-tpstart.tv_sec)
				+ tpend.tv_usec-tpstart.tv_usec;
		timeuse /= 1000000;
		FTS_DEBUG("[UPGRADE]: upgrade success : Use time: %d Seconds!!",
							timeuse);
>>>>>>> FETCH_HEAD
	}
#endif
}

/************************************************************************
<<<<<<< HEAD
* Name: fts_ctpm_auto_upgrade
* Brief:  0
* Input:  0
* Output: 0
* Return: 0
***********************************************************************/
int fts_ctpm_auto_upgrade(struct i2c_client *client)
{
	int i_ret = 0;
	static int uc_ErrorTimes = 0;
	static int uc_UpgradeTimes = 0;

	wakeup_source_init(&ps_lock, "tp_wakelock");

	__pm_stay_awake(&ps_lock);
=======
 * Name: fts_ctpm_auto_upgrade
 * Brief:  0
 * Input:  0
 * Output: 0
 * Return: 0
 ***********************************************************************/
int fts_ctpm_auto_upgrade(struct i2c_client *client)
{
	int i_ret = 0;
	static int uc_ErrorTimes;
	static int uc_UpgradeTimes;


	device_init_wakeup(&client->dev, 1);
	pm_stay_awake(&client->dev);
>>>>>>> FETCH_HEAD

	/* (FTS_GET_VENDOR_ID_NUM == 0) */
	g_fw_file = CTPM_FW;
	g_fw_len = fts_getsize(FW_SIZE);
	FTS_DEBUG("[UPGRADE]FW FILE:CTPM_FW, SIZE:%x", g_fw_len);

<<<<<<< HEAD
	do
	{
		uc_UpgradeTimes++;

		FTS_DEBUG_UPGRADE("start to upgrade %d times !!", uc_UpgradeTimes);
=======
	do {
		uc_UpgradeTimes++;

		FTS_DEBUG_UPGRADE("start to upgrade %d times !!",
				uc_UpgradeTimes);
>>>>>>> FETCH_HEAD

		fts_ctpm_display_upgrade_time(true);

		i_ret = fts_ctpm_auto_upgrade_pingpong(client);
		if (i_ret == 0)
<<<<<<< HEAD
		{
			fts_ctpm_display_upgrade_time(false);
		}
		else
		{
			uc_ErrorTimes++;
		}

		FTS_DEBUG_UPGRADE("upgrade %d times, error %d times!!", uc_UpgradeTimes, uc_ErrorTimes);
	}
	while (uc_UpgradeTimes < (FTS_UPGRADE_TEST_NUMBER));

	__pm_relax(&ps_lock);
=======
			fts_ctpm_display_upgrade_time(false);
		else
			uc_ErrorTimes++;

		FTS_DEBUG_UPGRADE("upgrade %d times, error %d times!!",
				uc_UpgradeTimes, uc_ErrorTimes);
	} while (uc_UpgradeTimes < (FTS_UPGRADE_TEST_NUMBER));

	pm_relax(&client->dev);
	device_init_wakeup(&client->dev, 0);
>>>>>>> FETCH_HEAD

	return 0;
}
#endif

