
#ifndef INTERRUPT_ROUTINES_H
    #define INTERRUPT_ROUTINES_H
    
    #include "project.h"
    #include "I2C_Interface.h"
    #include "RegistersDefinition.h"
    
    /*10 bits resolution output data contained in two bytes */
  
    #define NUM_BYTES 2
    
    /* x, y, z axes */
    #define AXES 3
    
    /* flag to inform whether new data are available */
    volatile uint8_t new_data;
    
    /* array that contains data to send through UART */
    uint8_t packet_to_send[AXES*NUM_BYTES +2];
    
    CY_ISR_PROTO(Custom_ISR);
    
    #endif

/* [] END OF FILE */
