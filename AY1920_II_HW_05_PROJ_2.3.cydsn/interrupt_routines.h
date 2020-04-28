
#ifndef INTERRUPT_ROUTINES_H
    #define INTERRUPT_ROUTINES_H
    
    #include "project.h"
    #include "I2C_Interface.h"
    #include "RegistersDefinition.h"
    
    
    /* accelerometer's output data are sent through UART in 4 bytes for each axis 
    since they are saved in a long int (32 bits) */
    #define NUM_BYTES 4
    
    /* x, y, z axes */
    #define AXES 3
    
    /* flag to inform if new data are available */
    volatile uint8_t new_data;
    
    /* array that contains data to send through UART: 12 bytes (4 for each axis)
    + 2 bytes (header+tail) */
    uint8_t packet_to_send[AXES*NUM_BYTES +2];
    
    CY_ISR_PROTO(Custom_ISR);
    
    #endif

/* [] END OF FILE */
