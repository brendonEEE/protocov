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

#include "SystemMessenger.h"
#include "BluetoothComms.h"
#include "UserButtonControl.h"
#include "VehicleBatteryVoltage.h"
#include "SystemMessenger.h"
#include "PowerMonitoringAndControl.h"

QueueHandle_t sysMessegesQ;

volatile uint8_t sysQSize = 20;
uint8_t taskMessageQSize = 5;

const uint8_t msgStartSeq[2] = {0xF, 0xA};
const uint8_t msgEndSeq[2] =  {0xC, 0xE};

systemMessagePacket_t msgPacket;

powerMoConDataPacket_t pwrMonControlPacket;


static void TaskSystemMessenger( void *pvParameters )
{
	
    (void)pvParameters;
    
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;  
  
    xTaskHandle temp;
      
    sysMessegesQ = xQueueCreate( sysQSize, sizeof( systemMessagePacket_t ) );
    taskMessegesQ = xQueueCreate( sysQSize, sizeof( systemMessagePacket_t ) );
    powerMonConMessegesQ = xQueueCreate( taskMessageQSize, sizeof( powerMoConDataPacket_t ) );

       
	for( ;; )
	{
		
        
        xQueueReceive( sysMessegesQ, &msgPacket, portMAX_DELAY);
        
        switch(msgPacket.sourceTaskAdd)
        {
            
            case BLUETOOTH_COMMS_ID:
            
            break;
            
            case CANBUS_MESSAGE_READ_ID: 
            
            
            break;
            
            case SYSTEM_MESSENGER_ID:
            
            break;
            
            case USER_BUTTON_CONTROL:
            
            
            break;
            case VEHICLE_BATT_VOLTAGE_ID:
            
            //memcpy( &pwrMonControlPacket, msgPacket.payload, sizeof(powerMoConDataPacket_t));
            
            pwrMonControlPacket = *(powerMoConDataPacket_t*)&msgPacket.payload;
           
            xQueueSendToFront(powerMonConMessegesQ, &pwrMonControlPacket, 10);
            
            temp = getPowerMonitoringAndControlTaskHandle();
            
            
 
            xTaskNotifyGive(temp);
            
            break;
            
            default:
            
            break;
            
            
            
        }
        
        temp = getBluetoothCommsTaskHandle();
        
        
        vTaskDelay(1);
	}
	
}

uint64_t createSystemMsgPacket( systemMessagePacket_t * msg, void* payload , uint8_t size, uint8_t srcID, uint8_t pcktCount,  uint8_t pcktPos, uint64_t msgID, uint8_t priority )
{
    
    
    
    if( msg == NULL || payload == NULL  ) return ( 0 );
    
    memcpy( msg->payload, payload, size );

    if(msgID == 0)
    {
        
        msg->packetId = rand();
    }
    
    memcpy(msg->startSeq, msgStartSeq, sizeof(msgStartSeq) / sizeof(msgStartSeq[0]));
    memcpy(msg->endSeq, msgEndSeq, sizeof(msgEndSeq) / sizeof(msgEndSeq[0]));
    msg->packetCount = pcktCount;
    msg->packetPos = pcktPos;
    msg->sourceTaskAdd = srcID;
    msg->payloadpPriority = priority;
    
    return msg->packetId;
}

QueueHandle_t getSysMessegesgQ()
{

    return sysMessegesQ;

}

void startTaskSystemMessenger()
{
    TaskHandle_t xHandle = NULL; 
 	/* Create the task, storing the handle. */ 
	xTaskCreate(
		TaskSystemMessenger,    /* Function that implements the task. */ 
		"SystemMessenger",  /* Text name for the task. */ 
		128,                        /* Stack size in words, not bytes. */ 
		( void * ) 1,               /* Parameter passed into the task. */ 
		tskIDLE_PRIORITY,           /* Priority at which the task is created. */ 
	&xHandle );                     /* Used to pass out the created task's handle. */ 
    
    
}



/* [] END OF FILE */
