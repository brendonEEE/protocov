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

#include "VehicleBatteryVoltage.h"
#include "SystemMessenger.h"

static void TaskVehicleBatteryVoltage( void *pvParameters )
{
	
    (void)pvParameters;

    ClockVehicleBattVoltageADC_Start();
    VehicleBattVoltageAdc_Start();
    VehicleBattVoltageAdc_StartConvert();

    volatile uint16_t battVoltage_mV = 0;
    volatile uint16_t battVoltage_count = 0;
    
    systemMessagePacket_t datapack;
    
    uint16_t RawData;
    float LPF_Beta = 0.05; // 0<ß<1
    
    uint16_t filteredVoltage =0;
    
    
    battVoltage_count = VehicleBattVoltageAdc_GetResult16();
        
    VehicleBattVoltageAdc_CountsTo_mVolts( battVoltage_count );
        
    battVoltage_mV = VehicleBattVoltageAdc_CountsTo_mVolts( battVoltage_count );
    
    filteredVoltage = battVoltage_mV;
    
	for( ;; )
	{
		
        
        battVoltage_count = VehicleBattVoltageAdc_GetResult16();
        
        VehicleBattVoltageAdc_CountsTo_mVolts( battVoltage_count );
        
        battVoltage_mV = VehicleBattVoltageAdc_CountsTo_mVolts( battVoltage_count );
        
        
        // Function that brings Fresh Data into RawData
        filteredVoltage = filteredVoltage - (LPF_Beta * (filteredVoltage - battVoltage_mV));
        
        createSystemMsgPacket( &datapack, &filteredVoltage, sizeof(float), VEHICLE_BATT_VOLTAGE_ID,0,0,0);
        
        if( getSysMessegesgQ() == NULL ) continue;
        
        xQueueSendToBack( getSysMessegesgQ(),&datapack, portMAX_DELAY );
        
        vTaskDelay(10);
        
        
    }
}


        
       



void startTaskVehicleBatteryVoltage()
{
    TaskHandle_t xHandle = NULL; 
 	/* Create the task, storing the handle. */ 
	xTaskCreate(
		TaskVehicleBatteryVoltage,    /* Function that implements the task. */ 
		"VehicleBatteryVoltage",  /* Text name for the task. */ 
		128,                        /* Stack size in words, not bytes. */ 
		( void * ) 1,               /* Parameter passed into the task. */ 
		tskIDLE_PRIORITY,           /* Priority at which the task is created. */ 
	&xHandle );                     /* Used to pass out the created task's handle. */ 
    
    
}



/* [] END OF FILE */
