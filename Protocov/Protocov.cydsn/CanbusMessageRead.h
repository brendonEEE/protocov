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
#ifndef CanbusMessageRead_H
#define CanbusMessageRead_H
    
#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
    
typedef struct{
   
    VehicleCAN_REG_32 rxid;
    VehicleCAN_DATA_BYTES rxdata;
    uint8_t dlc;
    
}CANBusRXMessage_t;

void startTaskCanbusMessageRead();

#endif
/* [] END OF FILE */
