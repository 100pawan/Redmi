/*
 * frontend.h
 *
 * Copyright (C) 2000 Marcus Metzler <marcus@convergence.de>
 *		    Ralph  Metzler <ralph@convergence.de>
 *		    Holger Waechtler <holger@convergence.de>
 *		    Andre Draszik <ad@convergence.de>
 *		    for convergence integrated media GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#ifndef _DVBFRONTEND_H_
#define _DVBFRONTEND_H_

#include <linux/types.h>

<<<<<<< HEAD
/**
 * enum fe_caps - Frontend capabilities
 *
 * @FE_IS_STUPID:			There's something wrong at the
 *					frontend, and it can't report its
 *					capabilities.
 * @FE_CAN_INVERSION_AUTO:		Can auto-detect frequency spectral
 *					band inversion
 * @FE_CAN_FEC_1_2:			Supports FEC 1/2
 * @FE_CAN_FEC_2_3:			Supports FEC 2/3
 * @FE_CAN_FEC_3_4:			Supports FEC 3/4
 * @FE_CAN_FEC_4_5:			Supports FEC 4/5
 * @FE_CAN_FEC_5_6:			Supports FEC 5/6
 * @FE_CAN_FEC_6_7:			Supports FEC 6/7
 * @FE_CAN_FEC_7_8:			Supports FEC 7/8
 * @FE_CAN_FEC_8_9:			Supports FEC 8/9
 * @FE_CAN_FEC_AUTO:			Can auto-detect FEC
 * @FE_CAN_QPSK:			Supports QPSK modulation
 * @FE_CAN_QAM_16:			Supports 16-QAM modulation
 * @FE_CAN_QAM_32:			Supports 32-QAM modulation
 * @FE_CAN_QAM_64:			Supports 64-QAM modulation
 * @FE_CAN_QAM_128:			Supports 128-QAM modulation
 * @FE_CAN_QAM_256:			Supports 256-QAM modulation
 * @FE_CAN_QAM_AUTO:			Can auto-detect QAM modulation
 * @FE_CAN_TRANSMISSION_MODE_AUTO:	Can auto-detect transmission mode
 * @FE_CAN_BANDWIDTH_AUTO:		Can auto-detect bandwidth
 * @FE_CAN_GUARD_INTERVAL_AUTO:		Can auto-detect guard interval
 * @FE_CAN_HIERARCHY_AUTO:		Can auto-detect hierarchy
 * @FE_CAN_8VSB:			Supports 8-VSB modulation
 * @FE_CAN_16VSB:			Supporta 16-VSB modulation
 * @FE_HAS_EXTENDED_CAPS:		Unused
 * @FE_CAN_MULTISTREAM:			Supports multistream filtering
 * @FE_CAN_TURBO_FEC:			Supports "turbo FEC" modulation
 * @FE_CAN_2G_MODULATION:		Supports "2nd generation" modulation,
 *					e. g. DVB-S2, DVB-T2, DVB-C2
 * @FE_NEEDS_BENDING:			Unused
 * @FE_CAN_RECOVER:			Can recover from a cable unplug
 *					automatically
 * @FE_CAN_MUTE_TS:			Can stop spurious TS data output
 */
=======
enum fe_type {
	FE_QPSK,
	FE_QAM,
	FE_OFDM,
	FE_ATSC
};

>>>>>>> FETCH_HEAD
enum fe_caps {
	FE_IS_STUPID			= 0,
	FE_CAN_INVERSION_AUTO		= 0x1,
	FE_CAN_FEC_1_2			= 0x2,
	FE_CAN_FEC_2_3			= 0x4,
	FE_CAN_FEC_3_4			= 0x8,
	FE_CAN_FEC_4_5			= 0x10,
	FE_CAN_FEC_5_6			= 0x20,
	FE_CAN_FEC_6_7			= 0x40,
	FE_CAN_FEC_7_8			= 0x80,
	FE_CAN_FEC_8_9			= 0x100,
	FE_CAN_FEC_AUTO			= 0x200,
	FE_CAN_QPSK			= 0x400,
	FE_CAN_QAM_16			= 0x800,
	FE_CAN_QAM_32			= 0x1000,
	FE_CAN_QAM_64			= 0x2000,
	FE_CAN_QAM_128			= 0x4000,
	FE_CAN_QAM_256			= 0x8000,
	FE_CAN_QAM_AUTO			= 0x10000,
	FE_CAN_TRANSMISSION_MODE_AUTO	= 0x20000,
	FE_CAN_BANDWIDTH_AUTO		= 0x40000,
	FE_CAN_GUARD_INTERVAL_AUTO	= 0x80000,
	FE_CAN_HIERARCHY_AUTO		= 0x100000,
	FE_CAN_8VSB			= 0x200000,
	FE_CAN_16VSB			= 0x400000,
<<<<<<< HEAD
	FE_HAS_EXTENDED_CAPS		= 0x800000,
	FE_CAN_MULTISTREAM		= 0x4000000,
	FE_CAN_TURBO_FEC		= 0x8000000,
	FE_CAN_2G_MODULATION		= 0x10000000,
	FE_NEEDS_BENDING		= 0x20000000,
	FE_CAN_RECOVER			= 0x40000000,
	FE_CAN_MUTE_TS			= 0x80000000
};

/*
 * DEPRECATED: Should be kept just due to backward compatibility.
 */
enum fe_type {
	FE_QPSK,
	FE_QAM,
	FE_OFDM,
	FE_ATSC
};

/**
 * struct dvb_frontend_info - Frontend properties and capabilities
 *
 * @name:			Name of the frontend
 * @type:			**DEPRECATED**.
 *				Should not be used on modern programs,
 *				as a frontend may have more than one type.
 *				In order to get the support types of a given
 *				frontend, use :c:type:`DTV_ENUM_DELSYS`
 *				instead.
 * @frequency_min:		Minimal frequency supported by the frontend.
 * @frequency_max:		Minimal frequency supported by the frontend.
 * @frequency_stepsize:		All frequencies are multiple of this value.
 * @frequency_tolerance:	Frequency tolerance.
 * @symbol_rate_min:		Minimal symbol rate, in bauds
 *				(for Cable/Satellite systems).
 * @symbol_rate_max:		Maximal symbol rate, in bauds
 *				(for Cable/Satellite systems).
 * @symbol_rate_tolerance:	Maximal symbol rate tolerance, in ppm
 *				(for Cable/Satellite systems).
 * @notifier_delay:		**DEPRECATED**. Not used by any driver.
 * @caps:			Capabilities supported by the frontend,
 *				as specified in &enum fe_caps.
 *
 * .. note:
 *
 *    #. The frequencies are specified in Hz for Terrestrial and Cable
 *       systems.
 *    #. The frequencies are specified in kHz for Satellite systems.
 */
=======
	FE_HAS_EXTENDED_CAPS		= 0x800000,   /* We need more bitspace for newer APIs, indicate this. */
	FE_CAN_MULTISTREAM		= 0x4000000,  /* frontend supports multistream filtering */
	FE_CAN_TURBO_FEC		= 0x8000000,  /* frontend supports "turbo fec modulation" */
	FE_CAN_2G_MODULATION		= 0x10000000, /* frontend supports "2nd generation modulation" (DVB-S2) */
	FE_NEEDS_BENDING		= 0x20000000, /* not supported anymore, don't use (frontend requires frequency bending) */
	FE_CAN_RECOVER			= 0x40000000, /* frontend can recover from a cable unplug automatically */
	FE_CAN_MUTE_TS			= 0x80000000  /* frontend can stop spurious TS data output */
};

>>>>>>> FETCH_HEAD
struct dvb_frontend_info {
	char       name[128];
	enum fe_type type;	/* DEPRECATED. Use DTV_ENUM_DELSYS instead */
	__u32      frequency_min;
	__u32      frequency_max;
	__u32      frequency_stepsize;
	__u32      frequency_tolerance;
	__u32      symbol_rate_min;
	__u32      symbol_rate_max;
<<<<<<< HEAD
	__u32      symbol_rate_tolerance;
=======
	__u32      symbol_rate_tolerance;	/* ppm */
>>>>>>> FETCH_HEAD
	__u32      notifier_delay;		/* DEPRECATED */
	enum fe_caps caps;
};

<<<<<<< HEAD
/**
 * struct dvb_diseqc_master_cmd - DiSEqC master command
 *
 * @msg:
 *	DiSEqC message to be sent. It contains a 3 bytes header with:
 *	framing + address + command, and an optional argument
 *	of up to 3 bytes of data.
 * @msg_len:
 *	Length of the DiSEqC message. Valid values are 3 to 6.
 *
 * Check out the DiSEqC bus spec available on http://www.eutelsat.org/ for
 * the possible messages that can be used.
 */
struct dvb_diseqc_master_cmd {
	__u8 msg[6];
	__u8 msg_len;
};

/**
 * struct dvb_diseqc_slave_reply - DiSEqC received data
 *
 * @msg:
 *	DiSEqC message buffer to store a message received via DiSEqC.
 *	It contains one byte header with: framing and
 *	an optional argument of up to 3 bytes of data.
 * @msg_len:
 *	Length of the DiSEqC message. Valid values are 0 to 4,
 *	where 0 means no message.
 * @timeout:
 *	Return from ioctl after timeout ms with errorcode when
 *	no message was received.
 *
 * Check out the DiSEqC bus spec available on http://www.eutelsat.org/ for
 * the possible messages that can be used.
 */
struct dvb_diseqc_slave_reply {
	__u8 msg[4];
	__u8 msg_len;
	int  timeout;
};

/**
 * enum fe_sec_voltage - DC Voltage used to feed the LNBf
 *
 * @SEC_VOLTAGE_13:	Output 13V to the LNBf
 * @SEC_VOLTAGE_18:	Output 18V to the LNBf
 * @SEC_VOLTAGE_OFF:	Don't feed the LNBf with a DC voltage
 */
=======

/**
 *  Check out the DiSEqC bus spec available on http://www.eutelsat.org/ for
 *  the meaning of this struct...
 */
struct dvb_diseqc_master_cmd {
	__u8 msg [6];	/*  { framing, address, command, data [3] } */
	__u8 msg_len;	/*  valid values are 3...6  */
};

struct dvb_diseqc_slave_reply {
	__u8 msg [4];	/*  { framing, data [3] } */
	__u8 msg_len;	/*  valid values are 0...4, 0 means no msg  */
	int  timeout;	/*  return from ioctl after timeout ms with */
};			/*  errorcode when no message was received  */

>>>>>>> FETCH_HEAD
enum fe_sec_voltage {
	SEC_VOLTAGE_13,
	SEC_VOLTAGE_18,
	SEC_VOLTAGE_OFF
};

<<<<<<< HEAD
/**
 * enum fe_sec_tone_mode - Type of tone to be send to the LNBf.
 * @SEC_TONE_ON:	Sends a 22kHz tone burst to the antenna.
 * @SEC_TONE_OFF:	Don't send a 22kHz tone to the antenna (except
 *			if the ``FE_DISEQC_*`` ioctls are called).
 */
=======
>>>>>>> FETCH_HEAD
enum fe_sec_tone_mode {
	SEC_TONE_ON,
	SEC_TONE_OFF
};

<<<<<<< HEAD
/**
 * enum fe_sec_mini_cmd - Type of mini burst to be sent
 *
 * @SEC_MINI_A:		Sends a mini-DiSEqC 22kHz '0' Tone Burst to select
 *			satellite-A
 * @SEC_MINI_B:		Sends a mini-DiSEqC 22kHz '1' Data Burst to select
 *			satellite-B
 */
=======
>>>>>>> FETCH_HEAD
enum fe_sec_mini_cmd {
	SEC_MINI_A,
	SEC_MINI_B
};

/**
<<<<<<< HEAD
 * enum fe_status - Enumerates the possible frontend status.
 * @FE_NONE:		The frontend doesn't have any kind of lock.
 *			That's the initial frontend status
 * @FE_HAS_SIGNAL:	Has found something above the noise level.
 * @FE_HAS_CARRIER:	Has found a DVB signal.
 * @FE_HAS_VITERBI:	FEC inner coding (Viterbi, LDPC or other inner code).
 *			is stable.
 * @FE_HAS_SYNC:	Synchronization bytes was found.
 * @FE_HAS_LOCK:	DVB were locked and everything is working.
 * @FE_TIMEDOUT:	Fo lock within the last about 2 seconds.
 * @FE_REINIT:		Frontend was reinitialized, application is recommended
 *			to reset DiSEqC, tone and parameters.
 */
enum fe_status {
	FE_NONE			= 0x00,
=======
 * enum fe_status - enumerates the possible frontend status
 * @FE_HAS_SIGNAL:	found something above the noise level
 * @FE_HAS_CARRIER:	found a DVB signal
 * @FE_HAS_VITERBI:	FEC is stable
 * @FE_HAS_SYNC:	found sync bytes
 * @FE_HAS_LOCK:	everything's working
 * @FE_TIMEDOUT:	no lock within the last ~2 seconds
 * @FE_REINIT:		frontend was reinitialized, application is recommended
 *			to reset DiSEqC, tone and parameters
 */
enum fe_status {
>>>>>>> FETCH_HEAD
	FE_HAS_SIGNAL		= 0x01,
	FE_HAS_CARRIER		= 0x02,
	FE_HAS_VITERBI		= 0x04,
	FE_HAS_SYNC		= 0x08,
	FE_HAS_LOCK		= 0x10,
	FE_TIMEDOUT		= 0x20,
	FE_REINIT		= 0x40,
};

<<<<<<< HEAD
/**
 * enum fe_spectral_inversion - Type of inversion band
 *
 * @INVERSION_OFF:	Don't do spectral band inversion.
 * @INVERSION_ON:	Do spectral band inversion.
 * @INVERSION_AUTO:	Autodetect spectral band inversion.
 *
 * This parameter indicates if spectral inversion should be presumed or
 * not. In the automatic setting (``INVERSION_AUTO``) the hardware will try
 * to figure out the correct setting by itself. If the hardware doesn't
 * support, the DVB core will try to lock at the carrier first with
 * inversion off. If it fails, it will try to enable inversion.
 */
=======
>>>>>>> FETCH_HEAD
enum fe_spectral_inversion {
	INVERSION_OFF,
	INVERSION_ON,
	INVERSION_AUTO
};

<<<<<<< HEAD
/**
 * enum fe_code_rate - Type of Forward Error Correction (FEC)
 *
 *
 * @FEC_NONE: No Forward Error Correction Code
 * @FEC_1_2:  Forward Error Correction Code 1/2
 * @FEC_2_3:  Forward Error Correction Code 2/3
 * @FEC_3_4:  Forward Error Correction Code 3/4
 * @FEC_4_5:  Forward Error Correction Code 4/5
 * @FEC_5_6:  Forward Error Correction Code 5/6
 * @FEC_6_7:  Forward Error Correction Code 6/7
 * @FEC_7_8:  Forward Error Correction Code 7/8
 * @FEC_8_9:  Forward Error Correction Code 8/9
 * @FEC_AUTO: Autodetect Error Correction Code
 * @FEC_3_5:  Forward Error Correction Code 3/5
 * @FEC_9_10: Forward Error Correction Code 9/10
 * @FEC_2_5:  Forward Error Correction Code 2/5
 *
 * Please note that not all FEC types are supported by a given standard.
 */
=======
>>>>>>> FETCH_HEAD
enum fe_code_rate {
	FEC_NONE = 0,
	FEC_1_2,
	FEC_2_3,
	FEC_3_4,
	FEC_4_5,
	FEC_5_6,
	FEC_6_7,
	FEC_7_8,
	FEC_8_9,
	FEC_AUTO,
	FEC_3_5,
	FEC_9_10,
	FEC_2_5,
};

<<<<<<< HEAD
/**
 * enum fe_modulation - Type of modulation/constellation
 * @QPSK:	QPSK modulation
 * @QAM_16:	16-QAM modulation
 * @QAM_32:	32-QAM modulation
 * @QAM_64:	64-QAM modulation
 * @QAM_128:	128-QAM modulation
 * @QAM_256:	256-QAM modulation
 * @QAM_AUTO:	Autodetect QAM modulation
 * @VSB_8:	8-VSB modulation
 * @VSB_16:	16-VSB modulation
 * @PSK_8:	8-PSK modulation
 * @APSK_16:	16-APSK modulation
 * @APSK_32:	32-APSK modulation
 * @DQPSK:	DQPSK modulation
 * @QAM_4_NR:	4-QAM-NR modulation
 *
 * Please note that not all modulations are supported by a given standard.
 *
 */
=======
>>>>>>> FETCH_HEAD
enum fe_modulation {
	QPSK,
	QAM_16,
	QAM_32,
	QAM_64,
	QAM_128,
	QAM_256,
	QAM_AUTO,
	VSB_8,
	VSB_16,
	PSK_8,
	APSK_16,
	APSK_32,
	DQPSK,
	QAM_4_NR,
};

<<<<<<< HEAD
/**
 * enum fe_transmit_mode - Transmission mode
 *
 * @TRANSMISSION_MODE_AUTO:
 *	Autodetect transmission mode. The hardware will try to find the
 *	correct FFT-size (if capable) to fill in the missing parameters.
 * @TRANSMISSION_MODE_1K:
 *	Transmission mode 1K
 * @TRANSMISSION_MODE_2K:
 *	Transmission mode 2K
 * @TRANSMISSION_MODE_8K:
 *	Transmission mode 8K
 * @TRANSMISSION_MODE_4K:
 *	Transmission mode 4K
 * @TRANSMISSION_MODE_16K:
 *	Transmission mode 16K
 * @TRANSMISSION_MODE_32K:
 *	Transmission mode 32K
 * @TRANSMISSION_MODE_C1:
 *	Single Carrier (C=1) transmission mode (DTMB only)
 * @TRANSMISSION_MODE_C3780:
 *	Multi Carrier (C=3780) transmission mode (DTMB only)
 *
 * Please note that not all transmission modes are supported by a given
 * standard.
 */
=======
>>>>>>> FETCH_HEAD
enum fe_transmit_mode {
	TRANSMISSION_MODE_2K,
	TRANSMISSION_MODE_8K,
	TRANSMISSION_MODE_AUTO,
	TRANSMISSION_MODE_4K,
	TRANSMISSION_MODE_1K,
	TRANSMISSION_MODE_16K,
	TRANSMISSION_MODE_32K,
	TRANSMISSION_MODE_C1,
	TRANSMISSION_MODE_C3780,
};

<<<<<<< HEAD
/**
 * enum fe_guard_interval - Guard interval
 *
 * @GUARD_INTERVAL_AUTO:	Autodetect the guard interval
 * @GUARD_INTERVAL_1_128:	Guard interval 1/128
 * @GUARD_INTERVAL_1_32:	Guard interval 1/32
 * @GUARD_INTERVAL_1_16:	Guard interval 1/16
 * @GUARD_INTERVAL_1_8:		Guard interval 1/8
 * @GUARD_INTERVAL_1_4:		Guard interval 1/4
 * @GUARD_INTERVAL_19_128:	Guard interval 19/128
 * @GUARD_INTERVAL_19_256:	Guard interval 19/256
 * @GUARD_INTERVAL_PN420:	PN length 420 (1/4)
 * @GUARD_INTERVAL_PN595:	PN length 595 (1/6)
 * @GUARD_INTERVAL_PN945:	PN length 945 (1/9)
 *
 * Please note that not all guard intervals are supported by a given standard.
 */
=======
>>>>>>> FETCH_HEAD
enum fe_guard_interval {
	GUARD_INTERVAL_1_32,
	GUARD_INTERVAL_1_16,
	GUARD_INTERVAL_1_8,
	GUARD_INTERVAL_1_4,
	GUARD_INTERVAL_AUTO,
	GUARD_INTERVAL_1_128,
	GUARD_INTERVAL_19_128,
	GUARD_INTERVAL_19_256,
	GUARD_INTERVAL_PN420,
	GUARD_INTERVAL_PN595,
	GUARD_INTERVAL_PN945,
};

<<<<<<< HEAD
/**
 * enum fe_hierarchy - Hierarchy
 * @HIERARCHY_NONE:	No hierarchy
 * @HIERARCHY_AUTO:	Autodetect hierarchy (if supported)
 * @HIERARCHY_1:	Hierarchy 1
 * @HIERARCHY_2:	Hierarchy 2
 * @HIERARCHY_4:	Hierarchy 4
 *
 * Please note that not all hierarchy types are supported by a given standard.
 */
=======
>>>>>>> FETCH_HEAD
enum fe_hierarchy {
	HIERARCHY_NONE,
	HIERARCHY_1,
	HIERARCHY_2,
	HIERARCHY_4,
	HIERARCHY_AUTO
};

<<<<<<< HEAD
/**
 * enum fe_interleaving - Interleaving
 * @INTERLEAVING_NONE:	No interleaving.
 * @INTERLEAVING_AUTO:	Auto-detect interleaving.
 * @INTERLEAVING_240:	Interleaving of 240 symbols.
 * @INTERLEAVING_720:	Interleaving of 720 symbols.
 *
 * Please note that, currently, only DTMB uses it.
 */
=======
>>>>>>> FETCH_HEAD
enum fe_interleaving {
	INTERLEAVING_NONE,
	INTERLEAVING_AUTO,
	INTERLEAVING_240,
	INTERLEAVING_720,
};

<<<<<<< HEAD
/* DVBv5 property Commands */

=======
/* S2API Commands */
>>>>>>> FETCH_HEAD
#define DTV_UNDEFINED		0
#define DTV_TUNE		1
#define DTV_CLEAR		2
#define DTV_FREQUENCY		3
#define DTV_MODULATION		4
#define DTV_BANDWIDTH_HZ	5
#define DTV_INVERSION		6
#define DTV_DISEQC_MASTER	7
#define DTV_SYMBOL_RATE		8
#define DTV_INNER_FEC		9
#define DTV_VOLTAGE		10
#define DTV_TONE		11
#define DTV_PILOT		12
#define DTV_ROLLOFF		13
#define DTV_DISEQC_SLAVE_REPLY	14

/* Basic enumeration set for querying unlimited capabilities */
#define DTV_FE_CAPABILITY_COUNT	15
#define DTV_FE_CAPABILITY	16
#define DTV_DELIVERY_SYSTEM	17

/* ISDB-T and ISDB-Tsb */
#define DTV_ISDBT_PARTIAL_RECEPTION	18
#define DTV_ISDBT_SOUND_BROADCASTING	19

#define DTV_ISDBT_SB_SUBCHANNEL_ID	20
#define DTV_ISDBT_SB_SEGMENT_IDX	21
#define DTV_ISDBT_SB_SEGMENT_COUNT	22

#define DTV_ISDBT_LAYERA_FEC			23
#define DTV_ISDBT_LAYERA_MODULATION		24
#define DTV_ISDBT_LAYERA_SEGMENT_COUNT		25
#define DTV_ISDBT_LAYERA_TIME_INTERLEAVING	26

#define DTV_ISDBT_LAYERB_FEC			27
#define DTV_ISDBT_LAYERB_MODULATION		28
#define DTV_ISDBT_LAYERB_SEGMENT_COUNT		29
#define DTV_ISDBT_LAYERB_TIME_INTERLEAVING	30

#define DTV_ISDBT_LAYERC_FEC			31
#define DTV_ISDBT_LAYERC_MODULATION		32
#define DTV_ISDBT_LAYERC_SEGMENT_COUNT		33
#define DTV_ISDBT_LAYERC_TIME_INTERLEAVING	34

#define DTV_API_VERSION		35

#define DTV_CODE_RATE_HP	36
#define DTV_CODE_RATE_LP	37
#define DTV_GUARD_INTERVAL	38
#define DTV_TRANSMISSION_MODE	39
#define DTV_HIERARCHY		40

#define DTV_ISDBT_LAYER_ENABLED	41

#define DTV_STREAM_ID		42
#define DTV_ISDBS_TS_ID_LEGACY	DTV_STREAM_ID
#define DTV_DVBT2_PLP_ID_LEGACY	43

#define DTV_ENUM_DELSYS		44

/* ATSC-MH */
#define DTV_ATSCMH_FIC_VER		45
#define DTV_ATSCMH_PARADE_ID		46
#define DTV_ATSCMH_NOG			47
#define DTV_ATSCMH_TNOG			48
#define DTV_ATSCMH_SGN			49
#define DTV_ATSCMH_PRC			50
#define DTV_ATSCMH_RS_FRAME_MODE	51
#define DTV_ATSCMH_RS_FRAME_ENSEMBLE	52
#define DTV_ATSCMH_RS_CODE_MODE_PRI	53
#define DTV_ATSCMH_RS_CODE_MODE_SEC	54
#define DTV_ATSCMH_SCCC_BLOCK_MODE	55
#define DTV_ATSCMH_SCCC_CODE_MODE_A	56
#define DTV_ATSCMH_SCCC_CODE_MODE_B	57
#define DTV_ATSCMH_SCCC_CODE_MODE_C	58
#define DTV_ATSCMH_SCCC_CODE_MODE_D	59

#define DTV_INTERLEAVING			60
#define DTV_LNA					61

/* Quality parameters */
#define DTV_STAT_SIGNAL_STRENGTH	62
#define DTV_STAT_CNR			63
#define DTV_STAT_PRE_ERROR_BIT_COUNT	64
#define DTV_STAT_PRE_TOTAL_BIT_COUNT	65
#define DTV_STAT_POST_ERROR_BIT_COUNT	66
#define DTV_STAT_POST_TOTAL_BIT_COUNT	67
#define DTV_STAT_ERROR_BLOCK_COUNT	68
#define DTV_STAT_TOTAL_BLOCK_COUNT	69

#define DTV_MAX_COMMAND		DTV_STAT_TOTAL_BLOCK_COUNT

<<<<<<< HEAD
/**
 * enum fe_pilot - Type of pilot tone
 *
 * @PILOT_ON:	Pilot tones enabled
 * @PILOT_OFF:	Pilot tones disabled
 * @PILOT_AUTO:	Autodetect pilot tones
 */
=======
>>>>>>> FETCH_HEAD
enum fe_pilot {
	PILOT_ON,
	PILOT_OFF,
	PILOT_AUTO,
};

<<<<<<< HEAD
/**
 * enum fe_rolloff - Rolloff factor (also known as alpha)
 * @ROLLOFF_35:		Roloff factor: 35%
 * @ROLLOFF_20:		Roloff factor: 20%
 * @ROLLOFF_25:		Roloff factor: 25%
 * @ROLLOFF_AUTO:	Auto-detect the roloff factor.
 *
 * .. note:
 *
 *    Roloff factor of 35% is implied on DVB-S. On DVB-S2, it is default.
 */
enum fe_rolloff {
	ROLLOFF_35,
=======
enum fe_rolloff {
	ROLLOFF_35, /* Implied value in DVB-S, default for DVB-S2 */
>>>>>>> FETCH_HEAD
	ROLLOFF_20,
	ROLLOFF_25,
	ROLLOFF_AUTO,
};

<<<<<<< HEAD
/**
 * enum fe_delivery_system - Type of the delivery system
 *
 * @SYS_UNDEFINED:
 *	Undefined standard. Generally, indicates an error
 * @SYS_DVBC_ANNEX_A:
 *	Cable TV: DVB-C following ITU-T J.83 Annex A spec
 * @SYS_DVBC_ANNEX_B:
 *	Cable TV: DVB-C following ITU-T J.83 Annex B spec (ClearQAM)
 * @SYS_DVBC_ANNEX_C:
 *	Cable TV: DVB-C following ITU-T J.83 Annex C spec
 * @SYS_ISDBC:
 *	Cable TV: ISDB-C (no drivers yet)
 * @SYS_DVBT:
 *	Terrestrial TV: DVB-T
 * @SYS_DVBT2:
 *	Terrestrial TV: DVB-T2
 * @SYS_ISDBT:
 *	Terrestrial TV: ISDB-T
 * @SYS_ATSC:
 *	Terrestrial TV: ATSC
 * @SYS_ATSCMH:
 *	Terrestrial TV (mobile): ATSC-M/H
 * @SYS_DTMB:
 *	Terrestrial TV: DTMB
 * @SYS_DVBS:
 *	Satellite TV: DVB-S
 * @SYS_DVBS2:
 *	Satellite TV: DVB-S2
 * @SYS_TURBO:
 *	Satellite TV: DVB-S Turbo
 * @SYS_ISDBS:
 *	Satellite TV: ISDB-S
 * @SYS_DAB:
 *	Digital audio: DAB (not fully supported)
 * @SYS_DSS:
 *	Satellite TV: DSS (not fully supported)
 * @SYS_CMMB:
 *	Terrestrial TV (mobile): CMMB (not fully supported)
 * @SYS_DVBH:
 *	Terrestrial TV (mobile): DVB-H (standard deprecated)
 */
=======
>>>>>>> FETCH_HEAD
enum fe_delivery_system {
	SYS_UNDEFINED,
	SYS_DVBC_ANNEX_A,
	SYS_DVBC_ANNEX_B,
	SYS_DVBT,
	SYS_DSS,
	SYS_DVBS,
	SYS_DVBS2,
	SYS_DVBH,
	SYS_ISDBT,
	SYS_ISDBS,
	SYS_ISDBC,
	SYS_ATSC,
	SYS_ATSCMH,
	SYS_DTMB,
	SYS_CMMB,
	SYS_DAB,
	SYS_DVBT2,
	SYS_TURBO,
	SYS_DVBC_ANNEX_C,
};

<<<<<<< HEAD
/* backward compatibility definitions for delivery systems */
#define SYS_DVBC_ANNEX_AC	SYS_DVBC_ANNEX_A
#define SYS_DMBTH		SYS_DTMB /* DMB-TH is legacy name, use DTMB */

/* ATSC-MH specific parameters */

/**
 * enum atscmh_sccc_block_mode - Type of Series Concatenated Convolutional
 *				 Code Block Mode.
 *
 * @ATSCMH_SCCC_BLK_SEP:
 *	Separate SCCC: the SCCC outer code mode shall be set independently
 *	for each Group Region (A, B, C, D)
 * @ATSCMH_SCCC_BLK_COMB:
 *	Combined SCCC: all four Regions shall have the same SCCC outer
 *	code mode.
 * @ATSCMH_SCCC_BLK_RES:
 *	Reserved. Shouldn't be used.
 */
=======
/* backward compatibility */
#define SYS_DVBC_ANNEX_AC	SYS_DVBC_ANNEX_A
#define SYS_DMBTH SYS_DTMB /* DMB-TH is legacy name, use DTMB instead */

/* ATSC-MH */

>>>>>>> FETCH_HEAD
enum atscmh_sccc_block_mode {
	ATSCMH_SCCC_BLK_SEP      = 0,
	ATSCMH_SCCC_BLK_COMB     = 1,
	ATSCMH_SCCC_BLK_RES      = 2,
};

<<<<<<< HEAD
/**
 * enum atscmh_sccc_code_mode - Type of Series Concatenated Convolutional
 *				Code Rate.
 *
 * @ATSCMH_SCCC_CODE_HLF:
 *	The outer code rate of a SCCC Block is 1/2 rate.
 * @ATSCMH_SCCC_CODE_QTR:
 *	The outer code rate of a SCCC Block is 1/4 rate.
 * @ATSCMH_SCCC_CODE_RES:
 *	Reserved. Should not be used.
 */
=======
>>>>>>> FETCH_HEAD
enum atscmh_sccc_code_mode {
	ATSCMH_SCCC_CODE_HLF     = 0,
	ATSCMH_SCCC_CODE_QTR     = 1,
	ATSCMH_SCCC_CODE_RES     = 2,
};

<<<<<<< HEAD
/**
 * enum atscmh_rs_frame_ensemble - Reed Solomon(RS) frame ensemble.
 *
 * @ATSCMH_RSFRAME_ENS_PRI:	Primary Ensemble.
 * @ATSCMH_RSFRAME_ENS_SEC:	Secondary Ensemble.
 */
=======
>>>>>>> FETCH_HEAD
enum atscmh_rs_frame_ensemble {
	ATSCMH_RSFRAME_ENS_PRI   = 0,
	ATSCMH_RSFRAME_ENS_SEC   = 1,
};

<<<<<<< HEAD
/**
 * enum atscmh_rs_frame_mode - Reed Solomon (RS) frame mode.
 *
 * @ATSCMH_RSFRAME_PRI_ONLY:
 *	Single Frame: There is only a primary RS Frame for all Group
 *	Regions.
 * @ATSCMH_RSFRAME_PRI_SEC:
 *	Dual Frame: There are two separate RS Frames: Primary RS Frame for
 *	Group Region A and B and Secondary RS Frame for Group Region C and
 *	D.
 * @ATSCMH_RSFRAME_RES:
 *	Reserved. Shouldn't be used.
 */
=======
>>>>>>> FETCH_HEAD
enum atscmh_rs_frame_mode {
	ATSCMH_RSFRAME_PRI_ONLY  = 0,
	ATSCMH_RSFRAME_PRI_SEC   = 1,
	ATSCMH_RSFRAME_RES       = 2,
};

<<<<<<< HEAD
/**
 * enum atscmh_rs_code_mode
 * @ATSCMH_RSCODE_211_187:	Reed Solomon code (211,187).
 * @ATSCMH_RSCODE_223_187:	Reed Solomon code (223,187).
 * @ATSCMH_RSCODE_235_187:	Reed Solomon code (235,187).
 * @ATSCMH_RSCODE_RES:		Reserved. Shouldn't be used.
 */
=======
>>>>>>> FETCH_HEAD
enum atscmh_rs_code_mode {
	ATSCMH_RSCODE_211_187    = 0,
	ATSCMH_RSCODE_223_187    = 1,
	ATSCMH_RSCODE_235_187    = 2,
	ATSCMH_RSCODE_RES        = 3,
};

#define NO_STREAM_ID_FILTER	(~0U)
#define LNA_AUTO                (~0U)

<<<<<<< HEAD
/**
 * enum fecap_scale_params - scale types for the quality parameters.
 *
=======
struct dtv_cmds_h {
	char	*name;		/* A display name for debugging purposes */

	__u32	cmd;		/* A unique ID */

	/* Flags */
	__u32	set:1;		/* Either a set or get property */
	__u32	buffer:1;	/* Does this property use the buffer? */
	__u32	reserved:30;	/* Align */
};

/**
 * Scale types for the quality parameters.
>>>>>>> FETCH_HEAD
 * @FE_SCALE_NOT_AVAILABLE: That QoS measure is not available. That
 *			    could indicate a temporary or a permanent
 *			    condition.
 * @FE_SCALE_DECIBEL: The scale is measured in 0.001 dB steps, typically
<<<<<<< HEAD
 *		      used on signal measures.
 * @FE_SCALE_RELATIVE: The scale is a relative percentual measure,
 *		       ranging from 0 (0%) to 0xffff (100%).
 * @FE_SCALE_COUNTER: The scale counts the occurrence of an event, like
 *		      bit error, block error, lapsed time.
=======
 *		  used on signal measures.
 * @FE_SCALE_RELATIVE: The scale is a relative percentual measure,
 *			ranging from 0 (0%) to 0xffff (100%).
 * @FE_SCALE_COUNTER: The scale counts the occurrence of an event, like
 *			bit error, block error, lapsed time.
>>>>>>> FETCH_HEAD
 */
enum fecap_scale_params {
	FE_SCALE_NOT_AVAILABLE = 0,
	FE_SCALE_DECIBEL,
	FE_SCALE_RELATIVE,
	FE_SCALE_COUNTER
};

/**
 * struct dtv_stats - Used for reading a DTV status property
 *
<<<<<<< HEAD
 * @scale:	Filled with enum fecap_scale_params - the scale
 *		in usage for that parameter
 *
 * The ``{unnamed_union}`` may have either one of the values below:
 *
 * %svalue
 *	integer value of the measure, for %FE_SCALE_DECIBEL,
 *	used for dB measures. The unit is 0.001 dB.
 *
 * %uvalue
 *	unsigned integer value of the measure, used when @scale is
 *	either %FE_SCALE_RELATIVE or %FE_SCALE_COUNTER.
 *
 * For most delivery systems, this will return a single value for each
 * parameter.
 *
=======
 * @value:	value of the measure. Should range from 0 to 0xffff;
 * @scale:	Filled with enum fecap_scale_params - the scale
 *		in usage for that parameter
 *
 * For most delivery systems, this will return a single value for each
 * parameter.
>>>>>>> FETCH_HEAD
 * It should be noticed, however, that new OFDM delivery systems like
 * ISDB can use different modulation types for each group of carriers.
 * On such standards, up to 8 groups of statistics can be provided, one
 * for each carrier group (called "layer" on ISDB).
<<<<<<< HEAD
 *
 * In order to be consistent with other delivery systems, the first
 * value refers to the entire set of carriers ("global").
 *
 * @scale should use the value %FE_SCALE_NOT_AVAILABLE when
 * the value for the entire group of carriers or from one specific layer
 * is not provided by the hardware.
 *
 * @len should be filled with the latest filled status + 1.
 *
 * In other words, for ISDB, those values should be filled like::
 *
=======
 * In order to be consistent with other delivery systems, the first
 * value refers to the entire set of carriers ("global").
 * dtv_status:scale should use the value FE_SCALE_NOT_AVAILABLE when
 * the value for the entire group of carriers or from one specific layer
 * is not provided by the hardware.
 * st.len should be filled with the latest filled status + 1.
 *
 * In other words, for ISDB, those values should be filled like:
>>>>>>> FETCH_HEAD
 *	u.st.stat.svalue[0] = global statistics;
 *	u.st.stat.scale[0] = FE_SCALE_DECIBEL;
 *	u.st.stat.value[1] = layer A statistics;
 *	u.st.stat.scale[1] = FE_SCALE_NOT_AVAILABLE (if not available);
 *	u.st.stat.svalue[2] = layer B statistics;
 *	u.st.stat.scale[2] = FE_SCALE_DECIBEL;
 *	u.st.stat.svalue[3] = layer C statistics;
 *	u.st.stat.scale[3] = FE_SCALE_DECIBEL;
 *	u.st.len = 4;
 */
struct dtv_stats {
	__u8 scale;	/* enum fecap_scale_params type */
	union {
		__u64 uvalue;	/* for counters and relative scales */
		__s64 svalue;	/* for 0.001 dB measures */
	};
} __attribute__ ((packed));


#define MAX_DTV_STATS   4

<<<<<<< HEAD
/**
 * struct dtv_fe_stats - store Digital TV frontend statistics
 *
 * @len:	length of the statistics - if zero, stats is disabled.
 * @stat:	array with digital TV statistics.
 *
 * On most standards, @len can either be 0 or 1. However, for ISDB, each
 * layer is modulated in separate. So, each layer may have its own set
 * of statistics. If so, stat[0] carries on a global value for the property.
 * Indexes 1 to 3 means layer A to B.
 */
=======
>>>>>>> FETCH_HEAD
struct dtv_fe_stats {
	__u8 len;
	struct dtv_stats stat[MAX_DTV_STATS];
} __attribute__ ((packed));

<<<<<<< HEAD
/**
 * struct dtv_property - store one of frontend command and its value
 *
 * @cmd:	Digital TV command.
 * @reserved:	Not used.
 * @u:		Union with the values for the command.
 * @result:	Unused
 *
 * The @u union may have either one of the values below:
 *
 * %data
 *	an unsigned 32-bits number.
 * %st
 *	a &struct dtv_fe_stats array of statistics.
 * %buffer
 *	a buffer of up to 32 characters (currently unused).
 */
=======
>>>>>>> FETCH_HEAD
struct dtv_property {
	__u32 cmd;
	__u32 reserved[3];
	union {
		__u32 data;
		struct dtv_fe_stats st;
		struct {
			__u8 data[32];
			__u32 len;
			__u32 reserved1[3];
			void *reserved2;
		} buffer;
	} u;
	int result;
} __attribute__ ((packed));

/* num of properties cannot exceed DTV_IOCTL_MAX_MSGS per ioctl */
#define DTV_IOCTL_MAX_MSGS 64

<<<<<<< HEAD
/**
 * struct dtv_properties - a set of command/value pairs.
 *
 * @num:	amount of commands stored at the struct.
 * @props:	a pointer to &struct dtv_property.
 */
=======
>>>>>>> FETCH_HEAD
struct dtv_properties {
	__u32 num;
	struct dtv_property *props;
};

<<<<<<< HEAD
/*
 * When set, this flag will disable any zigzagging or other "normal" tuning
 * behavior. Additionally, there will be no automatic monitoring of the lock
 * status, and hence no frontend events will be generated. If a frontend device
 * is closed, this flag will be automatically turned off when the device is
 * reopened read-write.
 */
#define FE_TUNE_MODE_ONESHOT 0x01

/* Digital TV Frontend API calls */

#define FE_GET_INFO		   _IOR('o', 61, struct dvb_frontend_info)

#define FE_DISEQC_RESET_OVERLOAD   _IO('o', 62)
#define FE_DISEQC_SEND_MASTER_CMD  _IOW('o', 63, struct dvb_diseqc_master_cmd)
#define FE_DISEQC_RECV_SLAVE_REPLY _IOR('o', 64, struct dvb_diseqc_slave_reply)
#define FE_DISEQC_SEND_BURST       _IO('o', 65)  /* fe_sec_mini_cmd_t */

#define FE_SET_TONE		   _IO('o', 66)  /* fe_sec_tone_mode_t */
#define FE_SET_VOLTAGE		   _IO('o', 67)  /* fe_sec_voltage_t */
#define FE_ENABLE_HIGH_LNB_VOLTAGE _IO('o', 68)  /* int */

#define FE_READ_STATUS		   _IOR('o', 69, fe_status_t)
#define FE_READ_BER		   _IOR('o', 70, __u32)
#define FE_READ_SIGNAL_STRENGTH    _IOR('o', 71, __u16)
#define FE_READ_SNR		   _IOR('o', 72, __u16)
#define FE_READ_UNCORRECTED_BLOCKS _IOR('o', 73, __u32)

#define FE_SET_FRONTEND_TUNE_MODE  _IO('o', 81) /* unsigned int */
#define FE_GET_EVENT		   _IOR('o', 78, struct dvb_frontend_event)

#define FE_DISHNETWORK_SEND_LEGACY_CMD _IO('o', 80) /* unsigned int */

#define FE_SET_PROPERTY		   _IOW('o', 82, struct dtv_properties)
#define FE_GET_PROPERTY		   _IOR('o', 83, struct dtv_properties)

#if defined(__DVB_CORE__) || !defined (__KERNEL__)

/*
 * DEPRECATED: Everything below is deprecated in favor of DVBv5 API
 *
 * The DVBv3 only ioctls, structs and enums should not be used on
 * newer programs, as it doesn't support the second generation of
 * digital TV standards, nor supports newer delivery systems.
 * They also don't support modern frontends with usually support multiple
 * delivery systems.
 *
 * Drivers shouldn't use them.
 *
 * New applications should use DVBv5 delivery system instead
 */

/*
=======
#if defined(__DVB_CORE__) || !defined (__KERNEL__)

/*
 * DEPRECATED: The DVBv3 ioctls, structs and enums should not be used on
 * newer programs, as it doesn't support the second generation of digital
 * TV standards, nor supports newer delivery systems.
>>>>>>> FETCH_HEAD
 */

enum fe_bandwidth {
	BANDWIDTH_8_MHZ,
	BANDWIDTH_7_MHZ,
	BANDWIDTH_6_MHZ,
	BANDWIDTH_AUTO,
	BANDWIDTH_5_MHZ,
	BANDWIDTH_10_MHZ,
	BANDWIDTH_1_712_MHZ,
};

<<<<<<< HEAD
/* This is kept for legacy userspace support */
=======
/* This is needed for legacy userspace support */
>>>>>>> FETCH_HEAD
typedef enum fe_sec_voltage fe_sec_voltage_t;
typedef enum fe_caps fe_caps_t;
typedef enum fe_type fe_type_t;
typedef enum fe_sec_tone_mode fe_sec_tone_mode_t;
typedef enum fe_sec_mini_cmd fe_sec_mini_cmd_t;
typedef enum fe_status fe_status_t;
typedef enum fe_spectral_inversion fe_spectral_inversion_t;
typedef enum fe_code_rate fe_code_rate_t;
typedef enum fe_modulation fe_modulation_t;
typedef enum fe_transmit_mode fe_transmit_mode_t;
typedef enum fe_bandwidth fe_bandwidth_t;
typedef enum fe_guard_interval fe_guard_interval_t;
typedef enum fe_hierarchy fe_hierarchy_t;
typedef enum fe_pilot fe_pilot_t;
typedef enum fe_rolloff fe_rolloff_t;
typedef enum fe_delivery_system fe_delivery_system_t;

<<<<<<< HEAD
/* DVBv3 structs */

=======
>>>>>>> FETCH_HEAD
struct dvb_qpsk_parameters {
	__u32		symbol_rate;  /* symbol rate in Symbols per second */
	fe_code_rate_t	fec_inner;    /* forward error correction (see above) */
};

struct dvb_qam_parameters {
	__u32		symbol_rate; /* symbol rate in Symbols per second */
	fe_code_rate_t	fec_inner;   /* forward error correction (see above) */
	fe_modulation_t	modulation;  /* modulation type (see above) */
};

struct dvb_vsb_parameters {
	fe_modulation_t	modulation;  /* modulation type (see above) */
};

struct dvb_ofdm_parameters {
	fe_bandwidth_t      bandwidth;
	fe_code_rate_t      code_rate_HP;  /* high priority stream code rate */
	fe_code_rate_t      code_rate_LP;  /* low priority stream code rate */
	fe_modulation_t     constellation; /* modulation type (see above) */
	fe_transmit_mode_t  transmission_mode;
	fe_guard_interval_t guard_interval;
	fe_hierarchy_t      hierarchy_information;
};

struct dvb_frontend_parameters {
	__u32 frequency;     /* (absolute) frequency in Hz for DVB-C/DVB-T/ATSC */
			     /* intermediate frequency in kHz for DVB-S */
	fe_spectral_inversion_t inversion;
	union {
		struct dvb_qpsk_parameters qpsk;	/* DVB-S */
		struct dvb_qam_parameters  qam;		/* DVB-C */
		struct dvb_ofdm_parameters ofdm;	/* DVB-T */
		struct dvb_vsb_parameters vsb;		/* ATSC */
	} u;
};

struct dvb_frontend_event {
	fe_status_t status;
	struct dvb_frontend_parameters parameters;
};
<<<<<<< HEAD

/* DVBv3 API calls */

#define FE_SET_FRONTEND		   _IOW('o', 76, struct dvb_frontend_parameters)
#define FE_GET_FRONTEND		   _IOR('o', 77, struct dvb_frontend_parameters)

#endif
=======
#endif

#define FE_SET_PROPERTY		   _IOW('o', 82, struct dtv_properties)
#define FE_GET_PROPERTY		   _IOR('o', 83, struct dtv_properties)

/**
 * When set, this flag will disable any zigzagging or other "normal" tuning
 * behaviour. Additionally, there will be no automatic monitoring of the lock
 * status, and hence no frontend events will be generated. If a frontend device
 * is closed, this flag will be automatically turned off when the device is
 * reopened read-write.
 */
#define FE_TUNE_MODE_ONESHOT 0x01

#define FE_GET_INFO		   _IOR('o', 61, struct dvb_frontend_info)

#define FE_DISEQC_RESET_OVERLOAD   _IO('o', 62)
#define FE_DISEQC_SEND_MASTER_CMD  _IOW('o', 63, struct dvb_diseqc_master_cmd)
#define FE_DISEQC_RECV_SLAVE_REPLY _IOR('o', 64, struct dvb_diseqc_slave_reply)
#define FE_DISEQC_SEND_BURST       _IO('o', 65)  /* fe_sec_mini_cmd_t */

#define FE_SET_TONE		   _IO('o', 66)  /* fe_sec_tone_mode_t */
#define FE_SET_VOLTAGE		   _IO('o', 67)  /* fe_sec_voltage_t */
#define FE_ENABLE_HIGH_LNB_VOLTAGE _IO('o', 68)  /* int */

#define FE_READ_STATUS		   _IOR('o', 69, fe_status_t)
#define FE_READ_BER		   _IOR('o', 70, __u32)
#define FE_READ_SIGNAL_STRENGTH    _IOR('o', 71, __u16)
#define FE_READ_SNR		   _IOR('o', 72, __u16)
#define FE_READ_UNCORRECTED_BLOCKS _IOR('o', 73, __u32)

#define FE_SET_FRONTEND		   _IOW('o', 76, struct dvb_frontend_parameters)
#define FE_GET_FRONTEND		   _IOR('o', 77, struct dvb_frontend_parameters)
#define FE_SET_FRONTEND_TUNE_MODE  _IO('o', 81) /* unsigned int */
#define FE_GET_EVENT		   _IOR('o', 78, struct dvb_frontend_event)

#define FE_DISHNETWORK_SEND_LEGACY_CMD _IO('o', 80) /* unsigned int */
>>>>>>> FETCH_HEAD

#endif /*_DVBFRONTEND_H_*/
