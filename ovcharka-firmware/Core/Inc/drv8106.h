/*
*****************************************************************************
* @file    drv8106.h
* @brief   This file contains all the function prototypes for
*          the drv8106.c file meant to interact with TI DRV8106-Q1
*          half-bridge driver. (https://www.ti.com/lit/ds/symlink/drv8106-q1.pdf)
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

#define DRV8106_RW_MASK     (1 << 6) // Set bit for read and reset for write

/* SPI comms handler struct */
typedef struct {
    SPI_HandleTypeDef* spi_handler_ptr;
    GPIO_TypeDef* CS_PORT;
    uint16_t CS_PIN;
    uint16_t rxbuff;
} drv8106_spi;

typedef struct {
    drv8106_spi spi_instance;
}drv8106_t;

void drv8106_read_reg(drv8106_spi* spi_inst, uint8_t reg_addr);
void drv8106_write_reg(drv8106_spi* spi_inst, uint8_t reg_addr, uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /*__DRV8106_H__*/
