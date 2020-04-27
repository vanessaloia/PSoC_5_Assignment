/* 
* In this header file all the definitions of device and register's addresses
* and values to set are available
*
* Author: Vanessa Aloia
* Date: 26/04/2020
*/
#ifndef REGISTER_DEFINITION_H
    #define REGISTER_DEFINITION_H
    
    /*  7-bit I2C address of the accelerometer. */
    #define LIS3DH_DEVICE_ADDRESS 0x18

    /* accelerometer's control register 1 address */
    #define CTRL_REG_1 0x20

    /* accelerometer's control register 4 address */
    #define CTRL_REG_4 0x23

    /* accelerometer's status register address */
    #define STATUS_REG 0x27

    /*accelerometer's output registers for x, y, z data*/
    #define OUT_X_L 0x28

    #define OUT_X_H 0x29

    #define OUT_Y_L 0x2A
    
    #define OUT_Y_H 0x2B

    #define OUT_Z_L 0x2C

    #define OUT_Z_H 0x2D
     
    
    /* values of control register 1 and 4 to set the high resolution mode (HR),100 Hz rate  and FSR= 8g*/
    #define CTRL_REG_1_HR 0x57
    #define CTRL_REG_4_HR 0x18
    
    /* if new data are available the fourth bit of the register is set at 1 */
    #define STATUS_REG_NEW_DATA 0x8

#endif


/* [] END OF FILE */
