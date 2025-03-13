/*
*****************************************************************************
* @file    drv8106.h
* @brief   This file contains all the function prototypes for
*          the drv8106.c file meant to interact with TI DRV8106-Q1
*          half-bridge driver. 
*          Datasheet: (https://www.ti.com/lit/ds/symlink/drv8106-q1.pdf)
* @author  JV4K, 2025
*****************************************************************************/

/* Define to prevent recursive inclusion -----------------------------------*/
#ifndef __DRV8106_H__
#define __DRV8106_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio.h"
#include "spi.h"

/* ----------DRV8106q1 registers addresses------------*/
#define DRV8106_IC_STAT_1       0x0
#define DRV8106_VGS_VDS_STAT    0x1
#define DRV8106_IC_STAT_2       0x2
#define DRV8106_RSVD_STAT       0x3
#define DRV8106_IC_CTRL         0x4
#define DRV8106_BRG_CTRL        0x5
#define DRV8106_DRV_CTRL_1      0x6
#define DRV8106_DRV_CTRL_2      0x7
#define DRV8106_DRV_CTRL_3      0x8
#define DRV8106_VDS_CTRL_1      0x9
#define DRV8106_VDS_CTRL_2      0xA
#define DRV8106_OLSC_CTRL       0xB
#define DRV8106_UVOV_CTRL       0xC
#define DRV8106_CSA_CTRL        0xD

/* READ command mask*/
#define DRV8106_READ_MASK     (1 << 6) // Set bit for read and reset for write


/* IC_STAT_1 register masks (attention: READ-ONLY)*/
#define DRV8106_SPI_OK          (1 << 7)
#define DRV8106_POR             (1 << 6)
#define DRV8106_FAULT           (1 << 5)
#define DRV8106_WARN            (1 << 4)
#define DRV8106_DS_GS           (1 << 3)
#define DRV8106_UV              (1 << 2)
#define DRV8106_OV              (1 << 1)
#define DRV8106_OT              1


/* VGS_VDS_STAT register masks (attention: READ-ONLY)*/
#define DRV8106_VGS_H1          (1 << 7)
#define DRV8106_VGS_L1          (1 << 6)
#define DRV8106_VDS_H1          (1 << 3)
#define DRV8106_VDS_L1          (1 << 2)


/* IC_STAT_2 register masks (attention: READ-ONLY)*/
#define DRV8106_PVDD_UV         (1 << 7)
#define DRV8106_PVDD_OV         (1 << 6)
#define DRV8106_VCP_UV          (1 << 5)
#define DRV8106_OTW             (1 << 4)
#define DRV8106_OTSD            (1 << 3)
#define DRV8106_SCLK_FLT        (1 << 1)
#define DRV8106_ADDR_FLT        1


/* IC_CTRL_1 register masks (attention: READ-WRITE)*/
#define DRV8106_EN_DRV          (1 << 7)
#define DRV8106_SSC_DIS         (1 << 6)
#define DRV8106_IN1_EN_MODE     (1 << 5)

#define DRV8106_LOCK_UL         (0b011 << 1) // default (unlock)
#define DRV8106_LOCK_L          (0b110 << 1) // lock

#define DRV8106_CLR_FLT         1


/* BRG_CTRL register masks (attention: READ-WRITE)*/
#define DRV8106_VGS_HS_DIS      (1 << 7)
#define DRV8106_S_IN1_EN        (1 << 3)
#define DRV8106_S_HIZ1          (1 << 1)


/* DRV_CTRL_1 register masks (attention: READ-WRITE) */
// Higher 4 bits - High side peak source pull-up current
#define DRV8106_IDRVP_HS_05mA   (0b0000 << 4)
#define DRV8106_IDRVP_HS_1mA    (0b0001 << 4)
#define DRV8106_IDRVP_HS_2mA    (0b0010 << 4)
#define DRV8106_IDRVP_HS_3mA    (0b0011 << 4)
#define DRV8106_IDRVP_HS_4mA    (0b0100 << 4)
#define DRV8106_IDRVP_HS_6mA    (0b0101 << 4)
#define DRV8106_IDRVP_HS_8mA    (0b0110 << 4)
#define DRV8106_IDRVP_HS_12mA   (0b0111 << 4)
#define DRV8106_IDRVP_HS_16mA   (0b1000 << 4)
#define DRV8106_IDRVP_HS_20mA   (0b1001 << 4)
#define DRV8106_IDRVP_HS_24mA   (0b1010 << 4)
#define DRV8106_IDRVP_HS_28mA   (0b1011 << 4)
#define DRV8106_IDRVP_HS_31mA   (0b1100 << 4)
#define DRV8106_IDRVP_HS_40mA   (0b1101 << 4)
#define DRV8106_IDRVP_HS_48mA   (0b1110 << 4)
#define DRV8106_IDRVP_HS_62mA   (0b1111 << 4)

// Lower 4 bits - High side peak sink pull-down current
#define DRV8106_IDRVN_HS_05mA   (0b0000)
#define DRV8106_IDRVN_HS_1mA    (0b0001)
#define DRV8106_IDRVN_HS_2mA    (0b0010)
#define DRV8106_IDRVN_HS_3mA    (0b0011)
#define DRV8106_IDRVN_HS_4mA    (0b0100)
#define DRV8106_IDRVN_HS_6mA    (0b0101)
#define DRV8106_IDRVN_HS_8mA    (0b0110)
#define DRV8106_IDRVN_HS_12mA   (0b0111)
#define DRV8106_IDRVN_HS_16mA   (0b1000)
#define DRV8106_IDRVN_HS_20mA   (0b1001)
#define DRV8106_IDRVN_HS_24mA   (0b1010)
#define DRV8106_IDRVN_HS_28mA   (0b1011)
#define DRV8106_IDRVN_HS_31mA   (0b1100)
#define DRV8106_IDRVN_HS_40mA   (0b1101)
#define DRV8106_IDRVN_HS_48mA   (0b1110)
#define DRV8106_IDRVN_HS_62mA   (0b1111)


/* DRV_CTRL_2 register masks (attention: READ-WRITE) */
// Higher 4 bits - Low side peak source pull-up current
#define DRV8106_IDRVP_LS_05mA   (0b0000 << 4)
#define DRV8106_IDRVP_LS_1mA    (0b0001 << 4)
#define DRV8106_IDRVP_LS_2mA    (0b0010 << 4)
#define DRV8106_IDRVP_LS_3mA    (0b0011 << 4)
#define DRV8106_IDRVP_LS_4mA    (0b0100 << 4)
#define DRV8106_IDRVP_LS_6mA    (0b0101 << 4)
#define DRV8106_IDRVP_LS_8mA    (0b0110 << 4)
#define DRV8106_IDRVP_LS_12mA   (0b0111 << 4)
#define DRV8106_IDRVP_LS_16mA   (0b1000 << 4)
#define DRV8106_IDRVP_LS_20mA   (0b1001 << 4)
#define DRV8106_IDRVP_LS_24mA   (0b1010 << 4)
#define DRV8106_IDRVP_LS_28mA   (0b1011 << 4)
#define DRV8106_IDRVP_LS_31mA   (0b1100 << 4)
#define DRV8106_IDRVP_LS_40mA   (0b1101 << 4)
#define DRV8106_IDRVP_LS_48mA   (0b1110 << 4)
#define DRV8106_IDRVP_LS_62mA   (0b1111 << 4)

// Lower 4 bits - Low side peak sink pull-down current
#define DRV8106_IDRVN_LS_05mA   (0b0000)
#define DRV8106_IDRVN_LS_1mA    (0b0001)
#define DRV8106_IDRVN_LS_2mA    (0b0010)
#define DRV8106_IDRVN_LS_3mA    (0b0011)
#define DRV8106_IDRVN_LS_4mA    (0b0100)
#define DRV8106_IDRVN_LS_6mA    (0b0101)
#define DRV8106_IDRVN_LS_8mA    (0b0110)
#define DRV8106_IDRVN_LS_12mA   (0b0111)
#define DRV8106_IDRVN_LS_16mA   (0b1000)
#define DRV8106_IDRVN_LS_20mA   (0b1001)
#define DRV8106_IDRVN_LS_24mA   (0b1010)
#define DRV8106_IDRVN_LS_28mA   (0b1011)
#define DRV8106_IDRVN_LS_31mA   (0b1100)
#define DRV8106_IDRVN_LS_40mA   (0b1101)
#define DRV8106_IDRVN_LS_48mA   (0b1110)
#define DRV8106_IDRVN_LS_62mA   (0b1111)


/* DRV_CTRL_3 register masks (attention: READ-WRITE) */
// VGS_MODE - gate fault monitor mode
#define DRV8106_VGS_MODE_LATCHED    (0b00 << 6) // default
#define DRV8106_VGS_MODE_CBC        (0b01 << 6) // *cycle by cycle
#define DRV8106_VGS_MODE_WARN       (0b10 << 6)
#define DRV8106_VGS_MODE_OFF        (0b11 << 6)

// VGS_TDRV - VGS drive time and VDS monitor blanking time
#define DRV8106_VGS_TDRV_96us       (0b00 << 4)
#define DRV8106_VGS_TDRV_2us        (0b01 << 4)
#define DRV8106_VGS_TDRV_4us        (0b10 << 4) // default
#define DRV8106_VGS_TDRV_8us        (0b11 << 4)

// VGS_TDEAD - Insertable digital dead-time
#define DRV8106_VGS_TDEAD_0ns       (0b000 << 1) // default
#define DRV8106_VGS_TDEAD_250ns     (0b001 << 1)
#define DRV8106_VGS_TDEAD_500ns     (0b010 << 1)
#define DRV8106_VGS_TDEAD_750ns     (0b011 << 1)
#define DRV8106_VGS_TDEAD_1000ns    (0b100 << 1)
#define DRV8106_VGS_TDEAD_2000ns    (0b101 << 1)
#define DRV8106_VGS_TDEAD_4000ns    (0b110 << 1)
#define DRV8106_VGS_TDEAD_8000ns    (0b111 << 1)

#define DRV8106_VGS_IND             (1) // default is 0


/* VDS_CTRL_1 -  Control register for VDS overcurrent comparators. (READ-WRITE) TODO: desc like this for all regs */
// VDS_MODE - VDS overcurrent monitor mode
#define DRV8106_VDS_MODE_LATCHED    (0b00 << 6) // default
#define DRV8106_VDS_MODE_CBC        (0b01 << 6) // *cycle by cycle
#define DRV8106_VDS_MODE_WARN       (0b10 << 6)
#define DRV8106_VDS_MODE_OFF        (0b11 << 6)

#define DRV8106_VDS_DG_1us          (0b00 << 4)
#define DRV8106_VDS_DG_2us          (0b01 << 4)
#define DRV8106_VDS_DG_4us          (0b10 << 4) // default
#define DRV8106_VDS_DG_8us          (0b11 << 4)

// VDS_IDRVN - IDRVN gate pulldown current after VDS_OCP fault.
#define DRV8106_VDS_IDRVN_PRM       (0b00 << 2) // default (programmed - by TI ig)
#define DRV8106_VDS_IDRVN_8mA       (0b01 << 2)
#define DRV8106_VDS_IDRVN_31mA      (0b10 << 2)
#define DRV8106_VDS_IDRVN_62mA      (0b10 << 2)

#define DRV8106_VDS_LVL             (1 << 1) // default is 0
#define DRV8106_VDS_IND             (1) // default is 0




// TODO: Deprecated shit, remove and change to uint16_t in all funcs
typedef struct {
    uint8_t byte1;
    uint8_t byte2;
} drv8106_msg;

/* SPI comms handler struct */
typedef struct {
    SPI_HandleTypeDef* spi_handler_ptr;
    GPIO_TypeDef* CS_PORT;
    uint16_t CS_PIN;
    uint16_t rxbuff;
} drv8106_spi;


void drv8106_read_reg(drv8106_spi* spi_inst, uint8_t reg_addr);
void drv8106_write_reg(drv8106_spi* spi_inst, uint8_t reg_addr, uint8_t data);


void drv8106_en_drv(drv8106_spi* spi_inst);
void drv8106_disable_drv(drv8106_spi* spi_inst);

#ifdef __cplusplus
}
#endif

#endif /*__DRV8106_H__*/
