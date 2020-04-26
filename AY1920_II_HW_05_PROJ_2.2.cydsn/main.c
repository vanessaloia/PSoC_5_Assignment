/**
* Project 2.2
* In this project the registers of the acceleremeter are set to provide a 3 axis signal
* in normal mode with a sampling frequency of 100 Hz. 
* Every 10 ms the accelerometer's status register is read to verify if new data are available.
* If so, the accelerometer's output registers are read and data are sent through UART communication
* with 9600 bps of velocity. 
*
* Author: Vanessa Aloia
* Date: 26/04/2020
*/




// Include required header files
#include "I2C_Interface.h"
#include "project.h"
#include "stdio.h"
#include "RegistersDefinition.h"
#include "interrupt_routines.h"





int main(void)
{
    /* Enable global interrupts. */
    CyGlobalIntEnable; 
    
    /* flag's default value is set at 0 */
    new_data=0;

    /* Place your initialization/startup of the I2C and UART */
    I2C_Peripheral_Start();
    UART_Debug_Start();
    
    
    /*"The boot procedure is complete about 5 milliseconds after device power-up." */
    CyDelay(5); 
    
    /* String to print out messages on the UART */
    char message[50];

    /* Check which devices are present on the I2C bus */
    for (int i = 0 ; i < 128; i++)
    {
        if (I2C_Peripheral_IsDeviceConnected(i))
        {
            // print out the address is hex format
            sprintf(message, "Device 0x%02X is connected\r\n", i);
            UART_Debug_PutString(message); 
        }
        
    }
    
    
    /* SET THE REGISTERS TO READ THE ACCELEROMETER'S OUTPUT AT 100 HZ WITH 10-bit RESOLUTION
     (NORMALE MODE)
    */
    
    uint8_t ctrl_reg;
    ErrorCode error;
   
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,CTRL_REG_1,&ctrl_reg);
    
    if (error == ERROR) {
        
        sprintf(message, "Error occurred while reading CTRL_REG_1\r\n");
        
        UART_Debug_PutString(message);
    }
    
    else {
         sprintf(message, "CTRL_REG_1 default value: 0x%02X \r\n", ctrl_reg);
        
         UART_Debug_PutString(message); 
    }
    
    /* Set the control register 1 in order to operate in normal mode at 100 Hz */
    if (ctrl_reg != CTRL_REG_1_NM) {
        ctrl_reg = CTRL_REG_1_NM;
        
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,CTRL_REG_1,ctrl_reg);
        
        if (error == ERROR) {
            
            sprintf(message,"Error occured while writing in CTRL_REG_1\r\n");
            UART_Debug_PutString(message);
        }
        else {
            sprintf(message, " CTRL_REG_1 set up at : 0x%02x\r\n", ctrl_reg);
            UART_Debug_PutString(message);
        }
    }
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,CTRL_REG_4,&ctrl_reg);
    
    if (error == ERROR) {
        sprintf(message, "Error occurred while reading CTRL_REG_4\r\n");
        UART_Debug_PutString(message);
    }
    
    else {
         sprintf(message, "CTRL_REG_4 default value: 0x%02X \r\n", ctrl_reg);
         UART_Debug_PutString(message); 
    }
    
    /* set the control register 4 to operate in normal mode */
    
    if (ctrl_reg != CTRL_REG_4_NM) {
        ctrl_reg = CTRL_REG_4_NM;
        
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,CTRL_REG_4,ctrl_reg);
        
        if (error == ERROR) {
            
            sprintf(message,"Error occured while writing in CTRL_REG_4\r\n");
            
            UART_Debug_PutString(message);
        }
        else {
            sprintf(message, " CTRL_REG_4 set up at : 0x%02x\r\n", ctrl_reg);
            
            UART_Debug_PutString(message);
        }
    }    
    
    /* after setting up the register, initialize timer and interrupt */
    Timer_Start();
    
    ISR_ReadData_StartEx(Custom_ISR);
    
    
    /* set header and tail for UART communication */
    packet_to_send[0]= 0xA0;
    packet_to_send[(AXES*NUM_BYTES+2)-1]= 0xC0;
    
    
    for(;;) {
        
        /* if new data are available */
        if (new_data) {
            
            /* sennd the data through UART */
            UART_Debug_PutArray(packet_to_send, AXES*NUM_BYTES +2);
            
            /* re-set the flag at 0 */
            new_data=0;
            
        }
        }
        
    }
    
    
