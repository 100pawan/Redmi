<<<<<<< HEAD
/* Copyright (c) 2017-2018, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2017-2018, 2020, The Linux Foundation. All rights reserved.
>>>>>>> FETCH_HEAD
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

<<<<<<< HEAD
#ifndef __MDSS_SPI_CLINET_H__
#define __MDSS_SPI_CLINET_H__

int mdss_spi_tx_command(const void *buf);
int mdss_spi_tx_parameter(const void *buf, size_t len);
int mdss_spi_tx_pixel(const void *buf, size_t len);
=======
#ifndef __MDSS_SPI_CLIENT_H__
#define __MDSS_SPI_CLIENT_H__

int mdss_spi_tx_command(const void *buf);
int mdss_spi_tx_parameter(const void *buf, size_t len);
#ifdef TARGET_HW_MDSS_MDP3
int mdp3_spi_tx_pixel(const void *buf, size_t len);
#else
int mdss_spi_tx_pixel(const void *buf, size_t len,
		void (*spi_tx_compelet)(void *), void *ctx);
#endif
>>>>>>> FETCH_HEAD
int mdss_spi_read_data(u8 reg_addr, u8 *data, u8 len);
#endif /* End of __MDSS_SPI_CLINET_H__ */
