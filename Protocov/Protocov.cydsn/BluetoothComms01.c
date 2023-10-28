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

#include "BluetoothComms.h"
#include "MessageConstructor.h"


extern uint8_t bluetoothDataAvailable;
extern BluetoothUartMsg_t bluetoothISRDataBuff[64];
extern uint64_t bluetoothMsgCount;

uint8_t bluetoothUserDataBuff[64];

TickType_t bluetoothRecTimeout_ms = 5;

const uint8_t msgStartSeq[2] = {0xF, 0xA};
const uint8_t msgEndSeq[2] =  {0xC, 0xE};

TaskHandle_t xHandle = NULL;



static void TaskBluetoothComms( void *pvParameters )
{
	
    (void)pvParameters;
    
    //IntBluetoothUART_Start();
    
    BluetoothUART_Start();
    IntBluetoothUART_Start();
    Clock_1_Start();
    Clock_2_Start();
    Counter_1_Start();
     
    uint16_t errorLog = 0;
    uint8_t readData = 0;
    uint32_t awoken = 0;
    
    for( ;; )
	{
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
     
        ulTaskNotifyTake( pdTRUE, pdMS_TO_TICKS( bluetoothRecTimeout_ms ) );
        
        if( bluetoothDataAvailable ==0 ) continue;

        bluetoothUserDataBuff[ bluetoothMsgCount -1] = bluetoothISRDataBuff[ bluetoothMsgCount -1 ].msg;
          
        BluetoothUART_WriteTxData(bluetoothUserDataBuff[ bluetoothMsgCount -1 ]);
        bluetoothDataAvailable = 0;
       
    }
}

TaskHandle_t getBluetoothCommsTaskHandle()
{
    
    return xHandle; 
}


void startTaskBluetoothComms()
{
    
    /* Create the task, storing the handle. */ 
	xTaskCreate(
		TaskBluetoothComms,      /* Function that implements the task. */ 
		"taskUserCodeGenerator",    /* Text name for the task. */ 
		128,                        /* Stack size in words, not bytes. */ 
		( void * ) 1,               /* Parameter passed into the task. */ 
		tskIDLE_PRIORITY,           /* Priority at which the task is created. */ 
	&xHandle );                     /* Used to pass out the created task's handle. */ 
    
}



/* [] END OF FILE */
