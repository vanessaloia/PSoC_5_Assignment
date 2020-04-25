
// Include required header files
#include "I2C_Interface.h"
#include "project.h"
#include "stdio.h"

/*  7-bit I2C address of the accelerometer. */
#define LIS3DH_DEVICE_ADDRESS 0x18

/* 8-bit control register 1 address of the accelerometer */
#define CTRL_REG_1 0x20

/* 8-bit control register 4 address of the accelerometer */
#define CTRL_REG_4 0x23

/*8-bit registers to read the X output */
#define OUT_X_L 0x28

#define OUT_X_H 0x29

#define OUT_Y_L 0x2A

#define OUT_Z_L 0x2B

#define OUT_Z_H 0x2D


/* set the normal mode (NM) and 100 Hz rate operating mode */

#define CTRL_REG_1_NM 0x57
#define CTRL_REG_4_NM 0x0



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Peripheral_Start();
    UART_Debug_Start();
    
    CyDelay(5); //"The boot procedure is complete about 5 milliseconds after device power-up."
    
    // String to print out messages on the UART
    char message[50];

    // Check which devices are present on the I2C bus
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
    uint8_t error;
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,CTRL_REG_1,&ctrl_reg);
    
    if (error == ERROR) {
        sprintf(message, "Error occurred while reading CTRL_REG_1\r\n");
        UART_Debug_PutString(message);
    }
    
    else {
         sprintf(message, "CTRL_REG_1 default value: 0x%02X \r\n", ctrl_reg);
         UART_Debug_PutString(message); 
    }
    
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
    
    for(;;) {
    }
    
    
}