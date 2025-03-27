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
#define DRV8106_IC_STAT_1       0x0 //read
#define DRV8106_VGS_VDS_STAT    0x1 //read
#define DRV8106_IC_STAT_2       0x2 //read
#define DRV8106_RSVD_STAT       0x3 //read
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


/* ----------DRV8106q1 registers default values------------*/
#define DRV8106_IC_STAT_1_DEFAULT       0x80
#define DRV8106_VGS_VDS_STAT_DEFAULT    0x0
#define DRV8106_IC_STAT_2_DEFAULT       0x10
#define DRV8106_RSVD_STAT_DEFAULT       0x0
#define DRV8106_IC_CTRL_DEFAULT         0x6
#define DRV8106_BRG_CTRL_DEFAULT        0x0
#define DRV8106_DRV_CTRL_1_DEFAULT      0xFF
#define DRV8106_DRV_CTRL_2_DEFAULT      0xFF
#define DRV8106_DRV_CTRL_3_DEFAULT      0x20
#define DRV8106_VDS_CTRL_1_DEFAULT      0x20
#define DRV8106_VDS_CTRL_2_DEFAULT      0xDD
#define DRV8106_OLSC_CTRL_DEFAULT       0x0
#define DRV8106_UVOV_CTRL_DEFAULT       0x14
#define DRV8106_CSA_CTRL_DEFAULT        0x1


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


/* VDS_CTRL_2 -   Control register for VDS threshold voltage. (READ-WRITE) */

// VDS_HS_LVL - High-side VDS overcurrent monitor threshold.
#define DRV8106_VDS_HS_LVL_60mV      (0b0000 << 4)
#define DRV8106_VDS_HS_LVL_80mV      (0b0001 << 4)
#define DRV8106_VDS_HS_LVL_100mV     (0b0010 << 4)
#define DRV8106_VDS_HS_LVL_120mV     (0b0011 << 4)
#define DRV8106_VDS_HS_LVL_140mV     (0b0100 << 4)
#define DRV8106_VDS_HS_LVL_160mV     (0b0101 << 4)
#define DRV8106_VDS_HS_LVL_180mV     (0b0110 << 4)
#define DRV8106_VDS_HS_LVL_200mV     (0b0111 << 4)
#define DRV8106_VDS_HS_LVL_300mV     (0b1000 << 4)
#define DRV8106_VDS_HS_LVL_400mV     (0b1001 << 4)
#define DRV8106_VDS_HS_LVL_500mV     (0b1010 << 4)
#define DRV8106_VDS_HS_LVL_600mV     (0b1011 << 4)
#define DRV8106_VDS_HS_LVL_700mV     (0b1100 << 4)
#define DRV8106_VDS_HS_LVL_1V        (0b1101 << 4)
#define DRV8106_VDS_HS_LVL_1V4       (0b1110 << 4)
#define DRV8106_VDS_HS_LVL_2V        (0b1111 << 4)

// VDS_LS_LVL - Low-side VDS overcurrent monitor threshold.
#define DRV8106_VDS_LS_LVL_60mV      (0b0000)
#define DRV8106_VDS_LS_LVL_80mV      (0b0001)
#define DRV8106_VDS_LS_LVL_100mV     (0b0010)
#define DRV8106_VDS_LS_LVL_120mV     (0b0011)
#define DRV8106_VDS_LS_LVL_140mV     (0b0100)
#define DRV8106_VDS_LS_LVL_160mV     (0b0101)
#define DRV8106_VDS_LS_LVL_180mV     (0b0110)
#define DRV8106_VDS_LS_LVL_200mV     (0b0111)
#define DRV8106_VDS_LS_LVL_300mV     (0b1000)
#define DRV8106_VDS_LS_LVL_400mV     (0b1001)
#define DRV8106_VDS_LS_LVL_500mV     (0b1010)
#define DRV8106_VDS_LS_LVL_600mV     (0b1011)
#define DRV8106_VDS_LS_LVL_700mV     (0b1100)
#define DRV8106_VDS_LS_LVL_1V        (0b1101)
#define DRV8106_VDS_LS_LVL_1V4       (0b1110)
#define DRV8106_VDS_LS_LVL_2V        (0b1111)

/* OLSC_CTRL - Control register for undervoltage and overvoltage monitors. (READ-WRITE) */
#define DRV8106_OLSC_EN              (1 << 4)
#define DRV8106_PU_SH1               (1 << 3)
#define DRV8106_PD_SH1               (1 << 2)


/* UVOV_CTRL -    Control register of offline diagnostics. (READ-WRITE) */
// PVDD supply undervoltage monitor mode. 0b = Latched fault (default). 1b = Automatic recovery.
#define DRV8106_PVDD_UV_MODE              (1 << 7)

// PVDD supply overvoltage monitor mode.
#define DRV8106_OV_MODE_LATCHED      (0b00 << 5)
#define DRV8106_OV_MODE_AUTO         (0b01 << 5)
#define DRV8106_OV_MODE_WARN         (0b10 << 5)
#define DRV8106_OV_MODE_OFF          (0b11 << 5)

// PVDD supply overvoltage monitor deglitch time.
#define DRV8106_OV_DG_1us            (0b00 << 3)
#define DRV8106_OV_DG_2us            (0b01 << 3)
#define DRV8106_OV_DG_4us            (0b10 << 3) // default
#define DRV8106_OV_DG_8us            (0b11 << 3)

// PVDD supply overvoltage monitor threshold.
#define DRV8106_OV_LVL               (1 << 2) // default is 1; 0b=21.5V; 1b=28.5V

// VCP charge pump undervoltage monitor mode.
#define DRV8106_UV_MODE              (1 << 7) // default is 0; 0b=Latched; 1b=Automatic recovery
#define VCP_UV_LVL                   (1) // default is 0; 0b=2.5V; 1b=5V


/* CSA_CTRL - Control register for current shunt amplifier. (READ-WRITE) */
#define DRV8106_CSA_SH_EN            (1 << 7) // 0b=Disabled (default); 1b=Enabled
#define DRV8106_CSA_BLK_SEL          (1 << 6) // Current shunt amplifier blanking trigger source. 0b = Half-bridge 1. 1b = Half-bridge 2

// TODO:
#define DRV8106_CSA_BLK

// TODO:
#define DRV8106_CSA_DIV

#define DRV8106_CSA_GAIN_10            (0b00)
#define DRV8106_CSA_GAIN_20            (0b01) // default
#define DRV8106_CSA_GAIN_40            (0b10)
#define DRV8106_CSA_GAIN_80            (0b11)


typedef struct {
    uint8_t IC_STAT_1;
    uint8_t VGS_VDS_STAT;
    uint8_t IC_STAT_2;
    uint8_t RSVD_STAT;
    uint8_t IC_CTRL;
    uint8_t BRG_CTRL;
    uint8_t DRV_CTRL_1;
    uint8_t DRV_CTRL_2;
    uint8_t DRV_CTRL_3;
    uint8_t VDS_CTRL_1;
    uint8_t VDS_CTRL_2;
    uint8_t OLSC_CTRL;
    uint8_t UVOV_CTRL;
    uint8_t CSA_CTRL;
} drv8106_registers;

typedef struct {
    uint8_t SPI_OK;
    uint8_t POR;
    uint8_t FAULT; // Indicates there is any fault present
    uint8_t WARN;
    uint8_t DS_GS;
    uint8_t Undervoltage;
    uint8_t Overvoltage;
    uint8_t Overtemperature;
} drv8106_faults;


/* SPI comms handler struct */
typedef struct {
    SPI_HandleTypeDef* spi_handler_ptr;
    GPIO_TypeDef* CS_PORT;
    uint16_t CS_PIN;
    uint16_t rxbuff;
    uint16_t txbuff;
    drv8106_registers register_map;
    drv8106_faults faults_list;
} drv8106_t;


void drv8106_read_reg_blocking(drv8106_t* spi_inst, uint8_t reg_addr);
void drv8106_write_reg_blocking(drv8106_t* spi_inst, uint8_t reg_addr, uint8_t data);

void drv8106_read_all_blocking(drv8106_t* spi_inst);
void drv8106_reset_blocking(drv8106_t* spi_inst);

void drv8106_read_reg_dma(drv8106_t* spi_inst, uint8_t reg_addr);

// void drv8106_Enable_dma(drv8106_t* spi_inst);
// void drv8106_Disable_dma(drv8106_t* spi_inst);

void drv8106_Enable_blocking(drv8106_t* drv_inst);
void drv8106_Disable_blocking(drv8106_t* drv_inst);

void drv8106_check_faults(drv8106_t* drv_inst);
void drv8106_clear_fault_blocking(drv8106_t* drv_inst);
void drv8106_set_fault_autorecovery_blocking(drv8106_t* drv_inst);
void drv8106_clear_fault_dma(drv8106_t* drv_inst);

void drv8106_CSA_enable_g10_blocking(drv8106_t* drv_inst);

/* GLOBAL INSTANCES AND VARIABLES */
extern drv8106_t drv_l1_dd6, drv_r1_dd7, drv_l2_dd8, drv_r2_dd9;
extern drv8106_t* drv_cur_ptr;
extern uint8_t drv8106_cur_read_addr;
extern uint8_t drv8106_read_flag;

#ifdef __cplusplus
}
#endif

#endif /* __DRV8106_H__ */
