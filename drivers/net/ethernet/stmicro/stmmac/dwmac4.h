/*
 * DWMAC4 Header file.
 *
 * Copyright (C) 2015  STMicroelectronics Ltd
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * Author: Alexandre Torgue <alexandre.torgue@st.com>
 */

#ifndef __DWMAC4_H__
#define __DWMAC4_H__

#include "common.h"

/*  MAC registers */
#define GMAC_CONFIG			0x00000000
#define GMAC_PACKET_FILTER		0x00000008
#define GMAC_HASH_TAB_0_31		0x00000010
#define GMAC_HASH_TAB_32_63		0x00000014
#define GMAC_RX_FLOW_CTRL		0x00000090
#define GMAC_QX_TX_FLOW_CTRL(x)		(0x70 + x * 4)
#define GMAC_TXQ_PRTY_MAP0		0x98
#define GMAC_TXQ_PRTY_MAP1		0x9C
#define GMAC_RXQ_CTRL0			0x000000a0
#define GMAC_RXQ_CTRL1			0x000000a4
#define GMAC_RXQ_CTRL2			0x000000a8
#define GMAC_RXQ_CTRL3			0x000000ac
#define GMAC_INT_STATUS			0x000000b0
#define GMAC_INT_EN			0x000000b4
#define GMAC_1US_TIC_COUNTER		0x000000dc
#define GMAC_PCS_BASE			0x000000e0
#define GMAC_PHYIF_CONTROL_STATUS	0x000000f8
#define GMAC_PMT			0x000000c0
#define GMAC_DEBUG			0x00000114
#define GMAC_HW_FEATURE0		0x0000011c
#define GMAC_HW_FEATURE1		0x00000120
#define GMAC_HW_FEATURE2		0x00000124
#define GMAC_HW_FEATURE3		0x00000128
#define GMAC_MDIO_ADDR			0x00000200
#define GMAC_MDIO_DATA			0x00000204
#define GMAC_ADDR_HIGH(reg)		(0x300 + reg * 8)
#define GMAC_ADDR_LOW(reg)		(0x304 + reg * 8)

/* RX Queues Routing */
#define GMAC_RXQCTRL_AVCPQ_MASK		GENMASK(2, 0)
#define GMAC_RXQCTRL_AVCPQ_SHIFT	0
#define GMAC_RXQCTRL_PTPQ_MASK		GENMASK(6, 4)
#define GMAC_RXQCTRL_PTPQ_SHIFT		4
#define GMAC_RXQCTRL_DCBCPQ_MASK	GENMASK(10, 8)
#define GMAC_RXQCTRL_DCBCPQ_SHIFT	8
#define GMAC_RXQCTRL_UPQ_MASK		GENMASK(14, 12)
#define GMAC_RXQCTRL_UPQ_SHIFT		12
#define GMAC_RXQCTRL_MCBCQ_MASK		GENMASK(18, 16)
#define GMAC_RXQCTRL_MCBCQ_SHIFT	16
#define GMAC_RXQCTRL_MCBCQEN		BIT(20)
#define GMAC_RXQCTRL_MCBCQEN_SHIFT	20
#define GMAC_RXQCTRL_TACPQE		BIT(21)
#define GMAC_RXQCTRL_TACPQE_SHIFT	21

/* MAC Packet Filtering */
#define GMAC_PACKET_FILTER_PR		BIT(0)
#define GMAC_PACKET_FILTER_HMC		BIT(2)
#define GMAC_PACKET_FILTER_PM		BIT(4)

#define GMAC_MAX_PERFECT_ADDRESSES	128

/* MAC RX Queue Enable */
#define GMAC_RX_QUEUE_CLEAR(queue)	~(GENMASK(1, 0) << ((queue) * 2))
#define GMAC_RX_AV_QUEUE_ENABLE(queue)	BIT((queue) * 2)
#define GMAC_RX_DCB_QUEUE_ENABLE(queue)	BIT(((queue) * 2) + 1)

/* MAC Flow Control RX */
#define GMAC_RX_FLOW_CTRL_RFE		BIT(0)

/* RX Queues Priorities */
#define GMAC_RXQCTRL_PSRQX_MASK(x)	GENMASK(7 + ((x) * 8), 0 + ((x) * 8))
#define GMAC_RXQCTRL_PSRQX_SHIFT(x)	((x) * 8)

/* TX Queues Priorities */
#define GMAC_TXQCTRL_PSTQX_MASK(x)	GENMASK(7 + ((x) * 8), 0 + ((x) * 8))
#define GMAC_TXQCTRL_PSTQX_SHIFT(x)	((x) * 8)

/* MAC Flow Control TX */
#define GMAC_TX_FLOW_CTRL_TFE		BIT(1)
#define GMAC_TX_FLOW_CTRL_PT_SHIFT	16

/*  MAC Interrupt bitmap*/
#define GMAC_INT_RGSMIIS		BIT(0)
#define GMAC_INT_PCS_LINK		BIT(1)
#define GMAC_INT_PCS_ANE		BIT(2)
#define GMAC_INT_PCS_PHYIS		BIT(3)
#define GMAC_INT_PMT_EN			BIT(4)
#define GMAC_INT_LPI_EN			BIT(5)

#define	GMAC_PCS_IRQ_DEFAULT	(GMAC_INT_RGSMIIS | GMAC_INT_PCS_LINK |	\
				 GMAC_INT_PCS_ANE)

#define	GMAC_INT_DEFAULT_ENABLE	(GMAC_INT_PMT_EN | GMAC_INT_LPI_EN)

enum dwmac4_irq_status {
	time_stamp_irq = 0x00001000,
	mmc_rx_csum_offload_irq = 0x00000800,
	mmc_tx_irq = 0x00000400,
	mmc_rx_irq = 0x00000200,
	mmc_irq = 0x00000100,
	lpi_irq = 0x00000020,
	pmt_irq = 0x00000010,
};

/* MAC PMT bitmap */
enum power_event {
	pointer_reset =	0x80000000,
	global_unicast = 0x00000200,
	wake_up_rx_frame = 0x00000040,
	magic_frame = 0x00000020,
	wake_up_frame_en = 0x00000004,
	magic_pkt_en = 0x00000002,
	power_down = 0x00000001,
};

/* Energy Efficient Ethernet (EEE) for GMAC4
 *
 * LPI status, timer and control register offset
 */
#define GMAC4_LPI_CTRL_STATUS	0xd0
#define GMAC4_LPI_TIMER_CTRL	0xd4

/* LPI control and status defines */
#define GMAC4_LPI_CTRL_STATUS_LPITCSE	BIT(21)	/* LPI Tx Clock Stop Enable */
#define GMAC4_LPI_CTRL_STATUS_LPITXA	BIT(19)	/* Enable LPI TX Automate */
#define GMAC4_LPI_CTRL_STATUS_PLS	BIT(17) /* PHY Link Status */
#define GMAC4_LPI_CTRL_STATUS_LPIEN	BIT(16)	/* LPI Enable */
#define GMAC4_LPI_CTRL_STATUS_RLPIEX	BIT(3) /* Receive LPI Exit */
#define GMAC4_LPI_CTRL_STATUS_RLPIEN	BIT(2) /* Receive LPI Entry */
#define GMAC4_LPI_CTRL_STATUS_TLPIEX	BIT(1) /* Transmit LPI Exit */
#define GMAC4_LPI_CTRL_STATUS_TLPIEN	BIT(0) /* Transmit LPI Entry */

/* MAC Debug bitmap */
#define GMAC_DEBUG_TFCSTS_MASK		GENMASK(18, 17)
#define GMAC_DEBUG_TFCSTS_SHIFT		17
#define GMAC_DEBUG_TFCSTS_IDLE		0
#define GMAC_DEBUG_TFCSTS_WAIT		1
#define GMAC_DEBUG_TFCSTS_GEN_PAUSE	2
#define GMAC_DEBUG_TFCSTS_XFER		3
#define GMAC_DEBUG_TPESTS		BIT(16)
#define GMAC_DEBUG_RFCFCSTS_MASK	GENMASK(2, 1)
#define GMAC_DEBUG_RFCFCSTS_SHIFT	1
#define GMAC_DEBUG_RPESTS		BIT(0)

/* MAC config */
#define GMAC_CONFIG_IPC			BIT(27)
#define GMAC_CONFIG_2K			BIT(22)
#define GMAC_CONFIG_ACS			BIT(20)
#define GMAC_CONFIG_BE			BIT(18)
#define GMAC_CONFIG_JD			BIT(17)
#define GMAC_CONFIG_JE			BIT(16)
#define GMAC_CONFIG_PS			BIT(15)
#define GMAC_CONFIG_FES			BIT(14)
#define GMAC_CONFIG_DM			BIT(13)
#define GMAC_CONFIG_DCRS		BIT(9)
#define GMAC_CONFIG_TE			BIT(1)
#define GMAC_CONFIG_RE			BIT(0)

/* MAC HW features0 bitmap */
#define GMAC_HW_FEAT_ADDMAC		BIT(18)
#define GMAC_HW_FEAT_RXCOESEL		BIT(16)
#define GMAC_HW_FEAT_TXCOSEL		BIT(14)
#define GMAC_HW_FEAT_EEESEL		BIT(13)
#define GMAC_HW_FEAT_TSSEL		BIT(12)
#define GMAC_HW_FEAT_MMCSEL		BIT(8)
#define GMAC_HW_FEAT_MGKSEL		BIT(7)
#define GMAC_HW_FEAT_RWKSEL		BIT(6)
#define GMAC_HW_FEAT_SMASEL		BIT(5)
#define GMAC_HW_FEAT_VLHASH		BIT(4)
#define GMAC_HW_FEAT_PCSSEL		BIT(3)
#define GMAC_HW_FEAT_HDSEL		BIT(2)
#define GMAC_HW_FEAT_GMIISEL		BIT(1)
#define GMAC_HW_FEAT_MIISEL		BIT(0)

/* MAC HW features1 bitmap */
#define GMAC_HW_FEAT_AVSEL		BIT(20)
#define GMAC_HW_TSOEN			BIT(18)
#define GMAC_HW_TXFIFOSIZE		GENMASK(10, 6)
#define GMAC_HW_RXFIFOSIZE		GENMASK(4, 0)

/* MAC HW features2 bitmap */
#define GMAC_HW_FEAT_PPSOUTNUM		GENMASK(26, 24)
#define GMAC_HW_FEAT_TXCHCNT		GENMASK(21, 18)
#define GMAC_HW_FEAT_RXCHCNT		GENMASK(15, 12)
#define GMAC_HW_FEAT_TXQCNT		GENMASK(9, 6)
#define GMAC_HW_FEAT_RXQCNT		GENMASK(3, 0)

/* MAC HW features3 bitmap */
#define GMAC_HW_FEAT_ASP		GENMASK(29, 28)
#define GMAC_HW_FEAT_FRPES		GENMASK(14, 13)
#define GMAC_HW_FEAT_FRPBS		GENMASK(12, 11)
#define GMAC_HW_FEAT_FRPSEL		BIT(10)

/* MAC HW ADDR regs */
#define GMAC_HI_DCS			GENMASK(18, 16)
#define GMAC_HI_DCS_SHIFT		16
#define GMAC_HI_REG_AE			BIT(31)

/*  MTL registers */
#define MTL_OPERATION_MODE		0x00000c00
#define MTL_FRPE			BIT(15)
#define MTL_OPERATION_SCHALG_MASK	GENMASK(6, 5)
#define MTL_OPERATION_SCHALG_WRR	(0x0 << 5)
#define MTL_OPERATION_SCHALG_WFQ	(0x1 << 5)
#define MTL_OPERATION_SCHALG_DWRR	(0x2 << 5)
#define MTL_OPERATION_SCHALG_SP		(0x3 << 5)
#define MTL_OPERATION_RAA		BIT(2)
#define MTL_OPERATION_RAA_SP		(0x0 << 2)
#define MTL_OPERATION_RAA_WSP		(0x1 << 2)

#define MTL_INT_STATUS			0x00000c20
#define MTL_INT_QX(x)			BIT(x)

#define MTL_RXQ_DMA_MAP0		0x00000c30 /* queue 0 to 3 */
#define MTL_RXQ_DMA_MAP1		0x00000c34 /* queue 4 to 7 */
#define MTL_RXQ_DMA_Q04MDMACH_MASK	GENMASK(3, 0)
#define MTL_RXQ_DMA_Q04MDMACH(x)	((x) << 0)
#define MTL_RXQ_DMA_QXMDMACH_MASK(x)	GENMASK(11 + (8 * ((x) - 1)), 8 * (x))
#define MTL_RXQ_DMA_QXMDMACH(chan, q)	((chan) << (8 * (q)))

#define MTL_CHAN_BASE_ADDR		0x00000d00
#define MTL_CHAN_BASE_OFFSET		0x40
#define MTL_CHANX_BASE_ADDR(x)		(MTL_CHAN_BASE_ADDR + \
					(x * MTL_CHAN_BASE_OFFSET))

#define MTL_CHAN_TX_OP_MODE(x)		MTL_CHANX_BASE_ADDR(x)
#define MTL_CHAN_TX_DEBUG(x)		(MTL_CHANX_BASE_ADDR(x) + 0x8)
#define MTL_CHAN_INT_CTRL(x)		(MTL_CHANX_BASE_ADDR(x) + 0x2c)
#define MTL_CHAN_RX_OP_MODE(x)		(MTL_CHANX_BASE_ADDR(x) + 0x30)
#define MTL_CHAN_RX_DEBUG(x)		(MTL_CHANX_BASE_ADDR(x) + 0x38)

#define MTL_OP_MODE_RSF			BIT(5)
#define MTL_OP_MODE_TXQEN_MASK		GENMASK(3, 2)
#define MTL_OP_MODE_TXQEN_AV		BIT(2)
#define MTL_OP_MODE_TXQEN		BIT(3)
#define MTL_OP_MODE_TSF			BIT(1)

#define MTL_OP_MODE_TQS_MASK		GENMASK(24, 16)
#define MTL_OP_MODE_TQS_SHIFT		16

#define MTL_OP_MODE_TTC_MASK		0x70
#define MTL_OP_MODE_TTC_SHIFT		4

#define MTL_OP_MODE_TTC_32		0
#define MTL_OP_MODE_TTC_64		(1 << MTL_OP_MODE_TTC_SHIFT)
#define MTL_OP_MODE_TTC_96		(2 << MTL_OP_MODE_TTC_SHIFT)
#define MTL_OP_MODE_TTC_128		(3 << MTL_OP_MODE_TTC_SHIFT)
#define MTL_OP_MODE_TTC_192		(4 << MTL_OP_MODE_TTC_SHIFT)
#define MTL_OP_MODE_TTC_256		(5 << MTL_OP_MODE_TTC_SHIFT)
#define MTL_OP_MODE_TTC_384		(6 << MTL_OP_MODE_TTC_SHIFT)
#define MTL_OP_MODE_TTC_512		(7 << MTL_OP_MODE_TTC_SHIFT)

#define MTL_OP_MODE_RQS_MASK		GENMASK(29, 20)
#define MTL_OP_MODE_RQS_SHIFT		20

#define MTL_OP_MODE_RFD_MASK		GENMASK(19, 14)
#define MTL_OP_MODE_RFD_SHIFT		14

#define MTL_OP_MODE_RFA_MASK		GENMASK(13, 8)
#define MTL_OP_MODE_RFA_SHIFT		8

#define MTL_OP_MODE_EHFC		BIT(7)

#define MTL_OP_MODE_RTC_MASK		0x18
#define MTL_OP_MODE_RTC_SHIFT		3

#define MTL_OP_MODE_RTC_32		(1 << MTL_OP_MODE_RTC_SHIFT)
#define MTL_OP_MODE_RTC_64		0
#define MTL_OP_MODE_RTC_96		(2 << MTL_OP_MODE_RTC_SHIFT)
#define MTL_OP_MODE_RTC_128		(3 << MTL_OP_MODE_RTC_SHIFT)

/* MTL ETS Control register */
#define MTL_ETS_CTRL_BASE_ADDR		0x00000d10
#define MTL_ETS_CTRL_BASE_OFFSET	0x40
#define MTL_ETSX_CTRL_BASE_ADDR(x)	(MTL_ETS_CTRL_BASE_ADDR + \
					((x) * MTL_ETS_CTRL_BASE_OFFSET))

#define MTL_ETS_CTRL_CC			BIT(3)
#define MTL_ETS_CTRL_AVALG		BIT(2)

/* MTL Queue Quantum Weight */
#define MTL_TXQ_WEIGHT_BASE_ADDR	0x00000d18
#define MTL_TXQ_WEIGHT_BASE_OFFSET	0x40
#define MTL_TXQX_WEIGHT_BASE_ADDR(x)	(MTL_TXQ_WEIGHT_BASE_ADDR + \
					((x) * MTL_TXQ_WEIGHT_BASE_OFFSET))
#define MTL_TXQ_WEIGHT_ISCQW_MASK	GENMASK(20, 0)

/* MTL sendSlopeCredit register */
#define MTL_SEND_SLP_CRED_BASE_ADDR	0x00000d1c
#define MTL_SEND_SLP_CRED_OFFSET	0x40
#define MTL_SEND_SLP_CREDX_BASE_ADDR(x)	(MTL_SEND_SLP_CRED_BASE_ADDR + \
					((x) * MTL_SEND_SLP_CRED_OFFSET))

#define MTL_SEND_SLP_CRED_SSC_MASK	GENMASK(13, 0)

/* MTL hiCredit register */
#define MTL_HIGH_CRED_BASE_ADDR		0x00000d20
#define MTL_HIGH_CRED_OFFSET		0x40
#define MTL_HIGH_CREDX_BASE_ADDR(x)	(MTL_HIGH_CRED_BASE_ADDR + \
					((x) * MTL_HIGH_CRED_OFFSET))

#define MTL_HIGH_CRED_HC_MASK		GENMASK(28, 0)

/* MTL loCredit register */
#define MTL_LOW_CRED_BASE_ADDR		0x00000d24
#define MTL_LOW_CRED_OFFSET		0x40
#define MTL_LOW_CREDX_BASE_ADDR(x)	(MTL_LOW_CRED_BASE_ADDR + \
					((x) * MTL_LOW_CRED_OFFSET))

#define MTL_HIGH_CRED_LC_MASK		GENMASK(28, 0)

/*  MTL debug */
#define MTL_DEBUG_TXSTSFSTS		BIT(5)
#define MTL_DEBUG_TXFSTS		BIT(4)
#define MTL_DEBUG_TWCSTS		BIT(3)

/* MTL debug: Tx FIFO Read Controller Status */
#define MTL_DEBUG_TRCSTS_MASK		GENMASK(2, 1)
#define MTL_DEBUG_TRCSTS_SHIFT		1
#define MTL_DEBUG_TRCSTS_IDLE		0
#define MTL_DEBUG_TRCSTS_READ		1
#define MTL_DEBUG_TRCSTS_TXW		2
#define MTL_DEBUG_TRCSTS_WRITE		3
#define MTL_DEBUG_TXPAUSED		BIT(0)

/* MAC debug: GMII or MII Transmit Protocol Engine Status */
#define MTL_DEBUG_RXFSTS_MASK		GENMASK(5, 4)
#define MTL_DEBUG_RXFSTS_SHIFT		4
#define MTL_DEBUG_RXFSTS_EMPTY		0
#define MTL_DEBUG_RXFSTS_BT		1
#define MTL_DEBUG_RXFSTS_AT		2
#define MTL_DEBUG_RXFSTS_FULL		3
#define MTL_DEBUG_RRCSTS_MASK		GENMASK(2, 1)
#define MTL_DEBUG_RRCSTS_SHIFT		1
#define MTL_DEBUG_RRCSTS_IDLE		0
#define MTL_DEBUG_RRCSTS_RDATA		1
#define MTL_DEBUG_RRCSTS_RSTAT		2
#define MTL_DEBUG_RRCSTS_FLUSH		3
#define MTL_DEBUG_RWCSTS		BIT(0)

/*  MTL interrupt */
#define MTL_RX_OVERFLOW_INT_EN		BIT(24)
#define MTL_RX_OVERFLOW_INT		BIT(16)

/* Default operating mode of the MAC */
#define GMAC_CORE_INIT (GMAC_CONFIG_JD | GMAC_CONFIG_PS | \
			GMAC_CONFIG_BE | GMAC_CONFIG_DCRS)

/* To dump the core regs excluding  the Address Registers */
#define	GMAC_REG_NUM	132

/*  MTL debug */
#define MTL_DEBUG_TXSTSFSTS		BIT(5)
#define MTL_DEBUG_TXFSTS		BIT(4)
#define MTL_DEBUG_TWCSTS		BIT(3)

/* MTL debug: Tx FIFO Read Controller Status */
#define MTL_DEBUG_TRCSTS_MASK		GENMASK(2, 1)
#define MTL_DEBUG_TRCSTS_SHIFT		1
#define MTL_DEBUG_TRCSTS_IDLE		0
#define MTL_DEBUG_TRCSTS_READ		1
#define MTL_DEBUG_TRCSTS_TXW		2
#define MTL_DEBUG_TRCSTS_WRITE		3
#define MTL_DEBUG_TXPAUSED		BIT(0)

/* MAC debug: GMII or MII Transmit Protocol Engine Status */
#define MTL_DEBUG_RXFSTS_MASK		GENMASK(5, 4)
#define MTL_DEBUG_RXFSTS_SHIFT		4
#define MTL_DEBUG_RXFSTS_EMPTY		0
#define MTL_DEBUG_RXFSTS_BT		1
#define MTL_DEBUG_RXFSTS_AT		2
#define MTL_DEBUG_RXFSTS_FULL		3
#define MTL_DEBUG_RRCSTS_MASK		GENMASK(2, 1)
#define MTL_DEBUG_RRCSTS_SHIFT		1
#define MTL_DEBUG_RRCSTS_IDLE		0
#define MTL_DEBUG_RRCSTS_RDATA		1
#define MTL_DEBUG_RRCSTS_RSTAT		2
#define MTL_DEBUG_RRCSTS_FLUSH		3
#define MTL_DEBUG_RWCSTS		BIT(0)

/* SGMII/RGMII status register */
#define GMAC_PHYIF_CTRLSTATUS_TC		BIT(0)
#define GMAC_PHYIF_CTRLSTATUS_LUD		BIT(1)
#define GMAC_PHYIF_CTRLSTATUS_SMIDRXS		BIT(4)
#define GMAC_PHYIF_CTRLSTATUS_LNKMOD		BIT(16)
#define GMAC_PHYIF_CTRLSTATUS_SPEED		GENMASK(18, 17)
#define GMAC_PHYIF_CTRLSTATUS_SPEED_SHIFT	17
#define GMAC_PHYIF_CTRLSTATUS_LNKSTS		BIT(19)
#define GMAC_PHYIF_CTRLSTATUS_JABTO		BIT(20)
#define GMAC_PHYIF_CTRLSTATUS_FALSECARDET	BIT(21)
/* LNKMOD */
#define GMAC_PHYIF_CTRLSTATUS_LNKMOD_MASK	0x1
/* LNKSPEED */
#define GMAC_PHYIF_CTRLSTATUS_SPEED_125		0x2
#define GMAC_PHYIF_CTRLSTATUS_SPEED_25		0x1
#define GMAC_PHYIF_CTRLSTATUS_SPEED_2_5		0x0

extern const struct stmmac_dma_ops dwmac4_dma_ops;
extern const struct stmmac_dma_ops dwmac410_dma_ops;
#endif /* __DWMAC4_H__ */
