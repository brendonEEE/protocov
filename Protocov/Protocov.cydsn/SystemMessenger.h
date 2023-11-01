/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef SystemMessenger_H
#define SystemMessenger_H
    

#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdlib.h>
    
 
    #define BLUETOOTH_COMMS_ID      0X01
    #define CANBUS_MESSAGE_READ_ID  0X02
    #define SYSTEM_MESSENGER_ID     0X03
    #define USER_BUTTON_CONTROL     0X04
    #define VEHICLE_BATT_VOLTAGE_ID 0X05

    
    
typedef struct  __attribute__((__packed__)){
    
    uint8_t startSeq[2];
    uint8_t endSeq[2];
    uint64_t packetId;
    uint8_t sourceTaskAdd;
    uint8_t payloadpPriority;
    uint8_t payload[48];
    uint8_t packetCount;
    uint8_t packetPos;
    
    
}systemMessagePacket_t;

typedef struct
{
    float vehicleBattVoltage;
    
}powerMoConDataPacket_t;

typedef struct
{
    
    uint8_t playPauseButton;
    uint8_t nextButton;
    uint8_t previousButton;
    uint8_t volumePlusButton;
    uint8_t volumeMinusButton;
    uint8_t keyPositionButton;
    
}userButtonInterface_t;

QueueHandle_t taskMessegesQ;
QueueHandle_t powerMonConMessegesQ;

 
uint64_t createSystemMsgPacket( systemMessagePacket_t * msg, void* payload , uint8_t size, uint8_t srcID, uint8_t pcktCount,  uint8_t pcktPos, uint64_t msgID, uint8_t priority  );
void startTaskSystemMessenger();

QueueHandle_t getSysMessegesgQ();

#endif
/* [] END OF FILE */
