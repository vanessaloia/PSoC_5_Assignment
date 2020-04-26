
#ifndef INTERRUPT_ROUTINES_H
    #define INTERRUPT_ROUTINES_H
    
    #include "project.h"
    #include "I2C_Interface.h"
    #include "RegistersDefinition.h"
    
    /* accelerometer's output data are contained in two bytes */
  
    #define NUM_BYTES 2
    
    /* x, y, z axes */
    #define AXES 3
    
    /* flag to inform if new data are available */
    volatile uint8_t new_data;
    
    /* array that contain data to send through UART */
    uint8_t packet_to_send[AXES*NUM_BYTES +2];
    
    CY_ISR_PROTO(Custom_ISR);
    
    #endif

/* [] END OF FILE */
