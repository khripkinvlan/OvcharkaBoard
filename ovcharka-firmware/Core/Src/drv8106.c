#include "drv8106.h"

void drv8106_read_reg(drv8106_spi* spi_inst, uint8_t reg_addr)
{
    HAL_GPIO_WritePin(spi_inst->CS_PORT, spi_inst->CS_PIN, GPIO_PIN_RESET);
    uint16_t tx = (reg_addr | DRV8106_RW_MASK) << 8;
    HAL_SPI_TransmitReceive(spi_inst->spi_handler_ptr, (uint8_t*)&tx, (uint8_t*)&spi_inst->rxbuff, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(spi_inst->CS_PORT, spi_inst->CS_PIN, GPIO_PIN_SET);
}

void drv8106_write_reg(drv8106_spi* spi_inst, uint8_t reg_addr, uint8_t data){
    HAL_GPIO_WritePin(spi_inst->CS_PORT, spi_inst->CS_PIN, GPIO_PIN_RESET);
    uint16_t tx = ((reg_addr | DRV8106_RW_MASK) << 8) | data;
    HAL_SPI_TransmitReceive(spi_inst->spi_handler_ptr, (uint8_t*)&tx, (uint8_t*)&spi_inst->rxbuff, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(spi_inst->CS_PORT, spi_inst->CS_PIN, GPIO_PIN_SET);
}