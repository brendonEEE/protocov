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
#ifndef BluetoothComms_H
#define BluetoothComms_H
    
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
    
void startTaskBluetoothComms();
TaskHandle_t getBluetoothCommsTaskHandle();

typedef struct
{

    uint8_t msg;
    TickType_t oldTickCount ;
    TickType_t newTickCount;
    
} BluetoothUartMsg_t;



#endif
/* [] END OF FILE */
