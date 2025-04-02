#include "potamon_bus_lowlvl_handle.h"

// Buffer to dump packets not intended to use on this level of control
uint8_t uart_rx_dump_buffer[20];

// Struct to recieve SYNC packets
pack_sync_t packet_sync;

// Struct to recieve CTRL packets
pack_data_ctrl_servo_t data_ctrl_unchecked, data_ctrl;

// Struct to pack feedback data
pack_data_encoder_t data_encoder;
pack_data_current_t data_current;

next_packet_t expected_packet; // Packet that is expected next

uint32_t bus_crc_history = 0xFFFFFFFF; // Here comes history of crc checks, 1 is ok 0 is fail. Last is LSB

// Counters for packets that failed crc check
uint32_t failed_sync_packets_count, failed_data_packets_count;

void update_crc_history(uint8_t crc_ok){
    bus_crc_history = (bus_crc_history << 1) | crc_ok;
}

uint8_t  get_crc_success_rate(){
    uint8_t success_count = __builtin_popcount(bus_crc_history);
    return (success_count * 100) / 32;
}

void pack_encoder_feedback(pack_data_encoder_t *packet) // Pack and crc encoder data
{
    packet->angle_1 = encoder_getAngle_iq18(&servo1_g.encoder) >> 9;
    packet->angle_1 = encoder_getAngle_iq18(&servo2_g.encoder) >> 9;
    packet->velocity_1 = (int16_t)(encoder_getVelocity_iq18(&servo1_g.encoder) >> 9);
    packet->velocity_2 = (int16_t)(encoder_getVelocity_iq18(&servo2_g.encoder) >> 9);
    packet->crc16 = crc16_ccitt((uint8_t*)packet, S_DATA_ENC_S1-2); // Using S1 size since they are same
}

void pack_current_feedback(pack_data_current_t *packet) // Pack and crc encoder data
{
    packet->current1 = (int16_t)(current[0] >> 9);
    packet->current2 = (int16_t)(current[1] >> 9);
    packet->crc16 = crc16_ccitt((uint8_t*)packet, S_DATA_CUR_S1-2); // Using S1 size since they are same
}

void sync_packet_handler(pack_sync_t *packet)
{
    switch (packet->ID)
    {
    case ID_S_STBY:
        system_enabled = 0;
        expected_packet = SYNC;
        HAL_UART_Receive_DMA(&huart1, (uint8_t *)&packet_sync, S_SYNC);
        data_ctrl.velocity_1 = 0;
        data_ctrl.velocity_2 = 0;
        break;
    case ID_S_VEL_CTRL:
        system_enabled = 1;
        control_mode = 0; // control velocity
        expected_packet = SYNC;
        HAL_UART_Receive_DMA(&huart1, (uint8_t *)&packet_sync, S_SYNC);
        break;
    case ID_S_ANG_CTRL:
        system_enabled = 1;
        control_mode = 1; // control angle
        expected_packet = SYNC;
        HAL_UART_Receive_DMA(&huart1, (uint8_t *)&packet_sync, S_SYNC);
        break;

    case ID_SYNC_CTRL_S1: // SYNC_CTRL_S1
        expected_packet = DATA_CTRL_S1;
        if (axis_define == 1)
        {
            HAL_UART_Receive_DMA(&huart1, (uint8_t *)&data_ctrl_unchecked, S_DATA_CTRL_S1);
        }
        else
        {
            HAL_UART_Receive_DMA(&huart1, uart_rx_dump_buffer, S_DATA_CTRL_S1);
        }
        break;
    case ID_SYNC_CTRL_S2: // SYNC_CTRL_S2
        expected_packet = DATA_CTRL_S2;
        if (axis_define == 2)
        {
            HAL_UART_Receive_DMA(&huart1, (uint8_t *)&data_ctrl_unchecked, S_DATA_CTRL_S2);
        }
        else
        {
            HAL_UART_Receive_DMA(&huart1, uart_rx_dump_buffer, S_DATA_CTRL_S2);
        }
        break;

    case ID_SYNC_ENC_S1: // SYNC_ENC_S1
        expected_packet = DATA_ENC_S1;
        if (axis_define == 1)
        {
            pack_encoder_feedback(&data_encoder);
            TXON; // Turn on transmission on Transceiver
            HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&data_encoder, S_DATA_ENC_S1);
        }
        else
        {
            HAL_UART_Receive_DMA(&huart1, uart_rx_dump_buffer, S_DATA_ENC_S1);
        }
        break;
    case ID_SYNC_ENC_S2: // SYNC_ENC_S2
        expected_packet = DATA_ENC_S2;
        if (axis_define == 2)
        {
            pack_encoder_feedback(&data_encoder);
            TXON; // Turn on transmission on Transceiver
            HAL_UART_Transmit_DMA(&huart1, (uint8_t*)&data_encoder, S_DATA_ENC_S2);
        }
        else
        {
            HAL_UART_Receive_DMA(&huart1, uart_rx_dump_buffer, S_DATA_ENC_S2);
        }
        break;
    case ID_SYNC_CUR_S1: // SYNC_CUR_S1
        expected_packet = DATA_CUR_S1;
        if (axis_define == 1)
        {
            pack_current_feedback(&data_current);
            TXON; // Turn on transmission on Transceiver
            HAL_UART_Transmit_DMA(&huart1, (uint8_t *)&data_current, S_DATA_CUR_S1);
        }
        else
        {
            HAL_UART_Receive_DMA(&huart1, uart_rx_dump_buffer, S_DATA_CUR_S1);
        }
        break;
    case ID_SYNC_CUR_S2: // SYNC_CUR_S2
        expected_packet = DATA_CUR_S2;
        if (axis_define == 2)
        {
            pack_current_feedback(&data_current);
            TXON; // Turn on transmission on Transceiver
            HAL_UART_Transmit_DMA(&huart1, (uint8_t *)&data_current, S_DATA_CUR_S2);
        }
        else
        {
            HAL_UART_Receive_DMA(&huart1, uart_rx_dump_buffer, S_DATA_CUR_S2);
        }
        break;
    default:
        break;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    switch (expected_packet)
    {
    case SYNC:
        if (packet_sync.crc8 == crc8_ccitt((uint8_t *)&packet_sync, 1))
        {
            update_crc_history(1);
            sync_packet_handler(&packet_sync);
        }
        else
        {
            update_crc_history(0);
            expected_packet = SYNC;
            HAL_UART_Receive_DMA(&huart1, (uint8_t *)&packet_sync, S_SYNC);
        }
        break;
    case DATA_CTRL_S1:
        if (axis_define == 1)
        {
            if (data_ctrl_unchecked.crc16 == crc16_ccitt((uint8_t *)&data_ctrl_unchecked, S_DATA_CTRL_S1 - 2))
            {
                update_crc_history(1);
                memcpy(&data_ctrl, &data_ctrl_unchecked, S_DATA_CTRL_S1);
            }
            else
            {
                update_crc_history(0);
                expected_packet = SYNC;
                HAL_UART_Receive_DMA(&huart1, (uint8_t *)&packet_sync, S_SYNC);
            }
        }
        expected_packet = SYNC;
        HAL_UART_Receive_DMA(&huart1, (uint8_t *)&packet_sync, S_SYNC);
        break;
    case DATA_CTRL_S2:
        if (axis_define == 2)
        {
            if (data_ctrl_unchecked.crc16 == crc16_ccitt((uint8_t *)&data_ctrl_unchecked, S_DATA_CTRL_S2 - 2))
            {
                update_crc_history(1);
                memcpy(&data_ctrl, &data_ctrl_unchecked, S_DATA_CTRL_S2);
            }
            else
            {
                update_crc_history(0);
                expected_packet = SYNC;
                HAL_UART_Receive_DMA(&huart1, (uint8_t *)&packet_sync, S_SYNC);
            }
        }
        expected_packet = SYNC;
        HAL_UART_Receive_DMA(&huart1, (uint8_t *)&packet_sync, S_SYNC);
        break;
    default:
        expected_packet = SYNC;
        HAL_UART_Receive_DMA(&huart1, (uint8_t *)&packet_sync, S_SYNC);
        break;
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    TXOFF; // Turn of transmission on transceiver in order to not hang the bus
    expected_packet = SYNC;
    HAL_UART_Receive_DMA(&huart1, (uint8_t *)&packet_sync, S_SYNC);
}