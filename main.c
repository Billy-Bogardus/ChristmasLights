/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F14K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "WS2812b/BitBangWS2812b.h"

#define DOWN        0
#define UP          1
#define SWITCH      PORTAbits.RA5
#define LED         LATCbits.LATC0
#define LED2        LATCbits.LATC1

#include <htc.h>   
/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    LED2 = 1;
    ADC1_Initialize();
    ADC1_SelectChannel(channel_AN10);
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    //WS_White(100, 2);
    unsigned short tmp = 51;
    int i=0;
    while (1)
    {
        tmp = ADC1_GetConversion(channel_AN10) * 51/1023;

        int brightness = (int) tmp;
        
        if (SWITCH == DOWN) {                         //switch is normally open to 5V ...when pressed, RA3 is connected to GND
            __delay_ms(10);                           //debounce by delaying and checking if switch is still pressed
            if (SWITCH == DOWN) {                     //check if still down
                LED = 1;                              //turn on DS1
                i++;
            }
        }
        else
            LED = 0; 
        LED2 = 0;
        if( !i )
        {
            WSWalk(50,brightness);
        }
        else if(i ==1)
        {
            WSSlow(100, brightness, 3);
        }
        else if(i == 2)
        {
            WSTest(100,brightness);
        }
        else
        {
            i = 0;
            LED2 = 1;
            __delay_ms(255);
            LED2 = 0; 
            __delay_ms(255); 
        }
        LED2 = 1;
    }
}
/**
 End of File
*/