#include "drv8106.h"

void drv8106_read_reg_blocking(drv8106_spi* spi_inst, uint8_t reg_addr)
{
    uint16_t tx = (reg_addr | DRV8106_READ_MASK) << 8;

    HAL_GPIO_WritePin(spi_inst->CS_PORT, spi_inst->CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(spi_inst->spi_handler_ptr, (uint8_t*)&tx, (uint8_t*)&spi_inst->rxbuff, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(spi_inst->CS_PORT, spi_inst->CS_PIN, GPIO_PIN_SET);
    // HAL_Delay(1); // in case it doesnt manage to flip CS
}

void drv8106_write_reg_blocking(drv8106_spi* spi_inst, uint8_t reg_addr, uint8_t data){
    uint16_t tx;
    tx = (reg_addr << 8) | data;

    HAL_GPIO_WritePin(spi_inst->CS_PORT, spi_inst->CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(spi_inst->spi_handler_ptr, (uint8_t*)&tx, (uint8_t*)&spi_inst->rxbuff, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(spi_inst->CS_PORT, spi_inst->CS_PIN, GPIO_PIN_SET);
    // HAL_Delay(1); // in case it doesnt manage to flip CS
}


void drv8106_read_all_blocking(drv8106_spi* spi_inst){
    drv8106_read_reg_blocking(spi_inst, DRV8106_IC_STAT_1);
    spi_inst->register_map.IC_STAT_1 = (uint8_t)(spi_inst->rxbuff & 0xFF);

    //TODO:
}

void drv8106_reset_blocking(drv8106_spi* spi_inst){

    drv8106_write_reg_blocking(spi_inst, DRV8106_IC_CTRL, DRV8106_IC_CTRL_DEFAULT);
    drv8106_write_reg_blocking(spi_inst, DRV8106_BRG_CTRL, DRV8106_BRG_CTRL_DEFAULT);
    drv8106_write_reg_blocking(spi_inst, DRV8106_DRV_CTRL_1, DRV8106_DRV_CTRL_1_DEFAULT);
    drv8106_write_reg_blocking(spi_inst, DRV8106_DRV_CTRL_2, DRV8106_DRV_CTRL_2_DEFAULT);
    drv8106_write_reg_blocking(spi_inst, DRV8106_DRV_CTRL_3, DRV8106_DRV_CTRL_3_DEFAULT);
    drv8106_write_reg_blocking(spi_inst, DRV8106_VDS_CTRL_1, DRV8106_VDS_CTRL_1_DEFAULT);
    drv8106_write_reg_blocking(spi_inst, DRV8106_VDS_CTRL_2, DRV8106_VDS_CTRL_2_DEFAULT);
    drv8106_write_reg_blocking(spi_inst, DRV8106_OLSC_CTRL, DRV8106_OLSC_CTRL_DEFAULT);
    drv8106_write_reg_blocking(spi_inst, DRV8106_UVOV_CTRL, DRV8106_UVOV_CTRL_DEFAULT);
    drv8106_write_reg_blocking(spi_inst, DRV8106_CSA_CTRL, DRV8106_CSA_CTRL_DEFAULT);
    
}