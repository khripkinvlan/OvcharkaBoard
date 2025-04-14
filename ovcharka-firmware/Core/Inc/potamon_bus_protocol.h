/*******************************************************
 * File: potamon_bus_protocol.h
 * Description: Header file with definitions of packet IDs, sizes
 *              and struct types for every packet used in potamon
 *              mecanum platform RS-485 bus communication
 * 
 * Author: JV4K
 * Created: January 5, 2025
 * Last Modified: January 10, 2025
 * 
 *******************************************************/
#ifndef __POTAMON_PROTOCOL_H__
#define __POTAMON_PROTOCOL_H__

#include "main.h"

// ========================================
//                PACKET IDS
// ========================================

// ----------- BROADCAST (MODE) SYNC packets IDs ------------
#define	ID_S_STBY	        0x00
#define	ID_S_VEL_CTRL	    0x01
#define	ID_S_ANG_CTRL	    0x02

// ----------- SYNC packets IDs ------------
#define	ID_SYNC_CTRL_S1	        0x06
#define	ID_SYNC_CTRL_S2	        0x07
#define	ID_SYNC_ENC_S1	        0x09
#define	ID_SYNC_ENC_S2	        0x0A
#define	ID_SYNC_CUR_S1	        0x0B
#define	ID_SYNC_CUR_S2	        0x0C


// ----------- DATA packets IDs: control ------------
#define	ID_DATA_CTRL_S1	        0x40
#define	ID_DATA_CTRL_S2	        0x41

// ----------- DATA packets IDs: feedback ------------
#define	ID_DATA_ENC_S1	        0x50
#define	ID_DATA_ENC_S2	        0x51
#define	ID_DATA_CUR_S1	        0x52
#define	ID_DATA_CUR_S2	        0x53


// ========================================
//            PACKET SIZES (BYTES)
// ========================================

// ----------- SYNC packets size ------------
#define S_SYNC           2

// ----------- SYNC packets sizes -----------
#define	S_DATA_CTRL_S1	        16
#define	S_DATA_CTRL_S2	        16

#define	S_DATA_ENC_S1	        15
#define	S_DATA_ENC_S2	        15
#define	S_DATA_CUR_S1	        8
#define	S_DATA_CUR_S2	        8


// ========================================
//         STRUCT TYPES FOR PACKETS
// ========================================

typedef struct 
{
    uint8_t ID;
    uint8_t crc8;
}__attribute__((packed)) pack_sync_t;

// Type for packet of DATA_CTRL_S1 (0x40) and DATA_CTRL_S2 (0x41)
typedef struct 
{
    uint8_t ID;
    int32_t angle_1;
    int16_t velocity_1;
    int32_t angle_2;
    int16_t velocity_2;
    uint8_t mode;
    uint16_t crc16;
}__attribute__((packed)) pack_data_ctrl_servo_t;

// Type for packets of DATA_ENC_S1 (0x50) and DATA_ENC_S2 (0x51)
typedef struct 
{
    uint8_t ID;
    int32_t angle_1;
    int16_t velocity_1;
    int32_t angle_2;
    int16_t velocity_2;
    uint16_t crc16;
}__attribute__((packed)) pack_data_encoder_t;

// Type for packets of DATA_CUR_S1 (0x52) and DATA_CUR_S2 (0x53)
typedef struct 
{
    uint8_t ID;
    int16_t current1;
    int16_t current2;
    uint8_t stat;
    uint16_t crc16;
}__attribute__((packed)) pack_data_current_t;

typedef enum
{
    SYNC,
    DATA_CTRL_S1,
    DATA_CTRL_S2,
    DATA_ENC_S1,
    DATA_ENC_S2,
    DATA_CUR_S1,
    DATA_CUR_S2,
} next_packet_t;

#endif