#include "drv8106.h"

drv8106_t drv_l1_dd6 = {&hspi1, SPI1_SS1_GPIO_Port, SPI1_SS1_Pin, 0};
drv8106_t drv_r1_dd7 = {&hspi1, SPI1_SS2_GPIO_Port, SPI1_SS2_Pin, 0};
drv8106_t drv_l2_dd8 = {&hspi1, SPI1_SS3_GPIO_Port, SPI1_SS3_Pin, 0};
drv8106_t drv_r2_dd9 = {&hspi1, SPI1_SS4_GPIO_Port, SPI1_SS4_Pin, 0};

drv8106_t* drv_cur_ptr;
uint8_t drv8106_cur_read_addr;
uint8_t drv8106_read_flag;


void drv8106_read_reg_blocking(drv8106_t* drv_inst, uint8_t reg_addr)
{
    uint16_t tx = (reg_addr | DRV8106_READ_MASK) << 8;

    HAL_GPIO_WritePin(drv_inst->CS_PORT, drv_inst->CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(drv_inst->spi_handler_ptr, (uint8_t*)&tx, (uint8_t*)&drv_inst->rxbuff, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(drv_inst->CS_PORT, drv_inst->CS_PIN, GPIO_PIN_SET);
    // HAL_Delay(1); // in case it doesnt manage to flip CS
}

void drv8106_write_reg_blocking(drv8106_t* drv_inst, uint8_t reg_addr, uint8_t data){
    uint16_t tx;
    tx = (reg_addr << 8) | data;

    HAL_GPIO_WritePin(drv_inst->CS_PORT, drv_inst->CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(drv_inst->spi_handler_ptr, (uint8_t*)&tx, (uint8_t*)&drv_inst->rxbuff, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(drv_inst->CS_PORT, drv_inst->CS_PIN, GPIO_PIN_SET);
    // HAL_Delay(1); // in case it doesnt manage to flip CS
}


void drv8106_read_all_blocking(drv8106_t* drv_inst){

    drv8106_read_reg_blocking(drv_inst, DRV8106_IC_STAT_1);
    drv_inst->register_map.IC_STAT_1 = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_VGS_VDS_STAT);
    drv_inst->register_map.VGS_VDS_STAT = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_IC_STAT_2);
    drv_inst->register_map.IC_STAT_2 = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_IC_CTRL);
    drv_inst->register_map.IC_CTRL = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_BRG_CTRL);
    drv_inst->register_map.BRG_CTRL = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_DRV_CTRL_1);
    drv_inst->register_map.DRV_CTRL_1 = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_DRV_CTRL_2);
    drv_inst->register_map.DRV_CTRL_2 = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_DRV_CTRL_3);
    drv_inst->register_map.DRV_CTRL_3 = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_VDS_CTRL_1);
    drv_inst->register_map.VDS_CTRL_1 = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_VDS_CTRL_2);
    drv_inst->register_map.VDS_CTRL_2 = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_OLSC_CTRL);
    drv_inst->register_map.OLSC_CTRL = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_UVOV_CTRL);
    drv_inst->register_map.UVOV_CTRL = (uint8_t)(drv_inst->rxbuff & 0xFF);

    drv8106_read_reg_blocking(drv_inst, DRV8106_CSA_CTRL);
    drv_inst->register_map.CSA_CTRL = (uint8_t)(drv_inst->rxbuff & 0xFF);
}

void drv8106_reset_blocking(drv8106_t* drv_inst){
    drv8106_write_reg_blocking(drv_inst, DRV8106_IC_CTRL, DRV8106_IC_CTRL_DEFAULT);
    drv8106_write_reg_blocking(drv_inst, DRV8106_BRG_CTRL, DRV8106_BRG_CTRL_DEFAULT);
    drv8106_write_reg_blocking(drv_inst, DRV8106_DRV_CTRL_1, DRV8106_DRV_CTRL_1_DEFAULT);
    drv8106_write_reg_blocking(drv_inst, DRV8106_DRV_CTRL_2, DRV8106_DRV_CTRL_2_DEFAULT);
    drv8106_write_reg_blocking(drv_inst, DRV8106_DRV_CTRL_3, DRV8106_DRV_CTRL_3_DEFAULT);
    drv8106_write_reg_blocking(drv_inst, DRV8106_VDS_CTRL_1, DRV8106_VDS_CTRL_1_DEFAULT);
    drv8106_write_reg_blocking(drv_inst, DRV8106_VDS_CTRL_2, DRV8106_VDS_CTRL_2_DEFAULT);
    drv8106_write_reg_blocking(drv_inst, DRV8106_OLSC_CTRL, DRV8106_OLSC_CTRL_DEFAULT);
    drv8106_write_reg_blocking(drv_inst, DRV8106_UVOV_CTRL, DRV8106_UVOV_CTRL_DEFAULT);
    drv8106_write_reg_blocking(drv_inst, DRV8106_CSA_CTRL, DRV8106_CSA_CTRL_DEFAULT);
}

void drv8106_read_reg_dma(drv8106_t* drv_inst, uint8_t reg_addr){
    drv8106_read_flag = 1;
    drv8106_cur_read_addr = reg_addr;
    uint16_t tx = (reg_addr | DRV8106_READ_MASK) << 8;
    drv_cur_ptr = drv_inst;

    HAL_GPIO_WritePin(drv_inst->CS_PORT, drv_inst->CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive_DMA(drv_inst->spi_handler_ptr, (uint8_t*)&tx, (uint8_t*)&drv_inst->rxbuff, 1);
}

void drv8106_write_reg_dma(drv8106_t* drv_inst, uint8_t reg_addr, uint8_t data){
    drv8106_read_flag = 0;
    uint16_t tx = (reg_addr << 8) | data;
    drv_cur_ptr = drv_inst;

    HAL_GPIO_WritePin(drv_inst->CS_PORT, drv_inst->CS_PIN, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive_DMA(drv_inst->spi_handler_ptr, (uint8_t*)&tx, (uint8_t*)&drv_inst->rxbuff, 1);
}

// // enable drv ic in non-blocking manner via dma
// void drv8106_Enable_dma(drv8106_t* drv_inst){
//     drv8106_write_reg_dma(drv_inst, DRV8106_IC_CTRL, DRV8106_EN_DRV);
// }

// // disable drv ic in non-blocking manner via dma
// void drv8106_Disable_dma(drv8106_t* drv_inst){
//     drv8106_write_reg_dma(drv_inst, DRV8106_IC_CTRL, 0);
// }

void drv8106_Enable_blocking(drv8106_t* drv_inst){
    drv8106_write_reg_blocking(drv_inst, DRV8106_IC_CTRL, DRV8106_EN_DRV);
}

void drv8106_Disable_blocking(drv8106_t* drv_inst){
    drv8106_write_reg_blocking(drv_inst, DRV8106_IC_CTRL, 0);
}

void drv8106_CSA_enable_g10_blocking(drv8106_t* drv_inst){
    drv8106_write_reg_blocking(drv_inst, DRV8106_CSA_CTRL, DRV8106_CSA_SH_EN | DRV8106_CSA_GAIN_10);
}

void drv8106_check_faults(drv8106_t* drv_inst){
    drv_inst->faults_list.FAULT = drv_inst->register_map.IC_STAT_1 & DRV8106_FAULT;
    drv_inst->faults_list.SPI_OK = drv_inst->register_map.IC_STAT_1 & DRV8106_SPI_OK;
    drv_inst->faults_list.POR = drv_inst->register_map.IC_STAT_1 & DRV8106_POR;
    drv_inst->faults_list.WARN = drv_inst->register_map.IC_STAT_1 & DRV8106_WARN;
    drv_inst->faults_list.DS_GS = drv_inst->register_map.IC_STAT_1 & DRV8106_DS_GS;
    drv_inst->faults_list.Undervoltage = drv_inst->register_map.IC_STAT_1 & DRV8106_UV;
    drv_inst->faults_list.Overvoltage = drv_inst->register_map.IC_STAT_1 & DRV8106_OV;
    drv_inst->faults_list.Overtemperature = drv_inst->register_map.IC_STAT_1 & DRV8106_OT;
}

void drv8106_clear_fault_blocking(drv8106_t* drv_inst){
    drv8106_write_reg_blocking(drv_inst, DRV8106_IC_CTRL, DRV8106_CLR_FLT);
}

void drv8106_set_fault_autorecovery_blocking(drv8106_t* drv_inst){
    uint8_t data = DRV8106_UV_MODE | DRV8106_OV_MODE_AUTO | DRV8106_OV_DG_4us | DRV8106_OV_LVL;
    drv8106_write_reg_blocking(drv_inst, DRV8106_UVOV_CTRL, data);
}

void drv8106_clear_fault_dma(drv8106_t* drv_inst){
    drv8106_write_reg_dma(drv_inst, DRV8106_IC_CTRL, DRV8106_CLR_FLT);
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
    if (hspi == drv_cur_ptr->spi_handler_ptr){
        HAL_GPIO_WritePin(drv_cur_ptr->CS_PORT, drv_cur_ptr->CS_PIN, GPIO_PIN_SET);
        if(drv8106_read_flag){
            switch (drv8106_cur_read_addr)
            {
            case DRV8106_IC_STAT_1:
                drv_cur_ptr->register_map.IC_STAT_1 = (uint8_t)(drv_cur_ptr->rxbuff & 0xFF);
                drv8106_check_faults(drv_cur_ptr);
                break;
            // TODO: rest cases
            default:
                break;
            }
        } else{
            uint8_t header_stat = (uint8_t)(drv_cur_ptr->rxbuff & 0xFF);
            uint8_t saved_stat_masked = drv_cur_ptr->register_map.IC_STAT_1 | 0x3F;
            drv_cur_ptr->register_map.IC_STAT_1 = header_stat & saved_stat_masked;
        }
    }
}