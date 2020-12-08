/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated driver implementation file for the ADC1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for ADC1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F14K22
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.30 and above
        MPLAB             :  MPLAB X 5.40
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "adc1.h"
#include "device_config.h"


/**
  Section: ADC Module APIs
*/

void (*ADC1_InterruptHandler)(void);

void ADC1_Initialize(void)
{
    // set the ADC1 to the options selected in the User Interface
    
    // NVCFG VSS; PVCFG VDD; 
    ADCON1 = 0x00;
    
    // ADFM right; ACQT 20; ADCS FOSC/64; 
    ADCON2 = 0xBE;
    
    // ADRESL 0; 
    ADRESL = 0x00;
    
    // ADRESH 0; 
    ADRESH = 0x00;
    
    // GO_nDONE stop; ADON enabled; CHS AN10; 
    ADCON0 = 0x29;
    
    // Enabling ADC1 interrupt.
    PIE1bits.ADIE = 1;
	
	// Set Default Interrupt Handler
    ADC1_SetInterruptHandler(ADC1_DefaultInterruptHandler);
}

void ADC1_SelectChannel(adc_channel_t channel)
{
    // select the A/D channel
    ADCON0bits.CHS = channel;    
    // Turn on the ADC module
    ADCON0bits.ADON = 1;  
}

void ADC1_StartConversion(void)
{
    // Start the conversion
    ADCON0bits.GO_nDONE = 1;
}


bool ADC1_IsConversionDone(void)
{
    // Start the conversion
    return ((bool)(!ADCON0bits.GO_nDONE));
}

adc_result_t ADC1_GetConversionResult(void)
{
    // Conversion finished, return the result
     return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

adc_result_t ADC1_GetConversion(adc_channel_t channel)
{
    // select the A/D channel
    ADCON0bits.CHS = channel;    

    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE)
    {
    }

    // Conversion finished, return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

void ADC1_TemperatureAcquisitionDelay(void)
{
    __delay_us(200);
}

void ADC1_ISR(void)
{
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
	
	if(ADC1_InterruptHandler)
    {
        ADC1_InterruptHandler();
    }
}

void ADC1_SetInterruptHandler(void (* InterruptHandler)(void)){
    ADC1_InterruptHandler = InterruptHandler;
}

void ADC1_DefaultInterruptHandler(void){
    // add your ADC1 interrupt custom code
    // or set custom function using ADC1_SetInterruptHandler()
}
/**
 End of File
*/