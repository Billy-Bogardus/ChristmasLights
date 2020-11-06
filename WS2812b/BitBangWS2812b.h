/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BB_WS2812B_Headder_H
#define	BB_WS2812B_Headder_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <htc.h> 
#include <stdint.h>

#define _XTAL_FREQ 32000000

#define WSReset 60.000 //Time in milli Seconds
#define WSPulse0H 0.400
#define WSPulse0L 0.850
#define WSPulse1H 0.800
#define WSPulse1L 0.450
#define WSTotal 1.250
#define WSERROR 0.150

// declare variables

/**
 * 
 * @param A Red
 * @param B Green
 * @param C Blue
 * @Example
    WS_Word(0xff, 0x00, 0x00);
 */
void WS_Word(int A, int B, int C);

/**
 * 
 * @param A int (basically true or false)
 */
void WS_Write(int);

/**
 * 
 */
void WSLoop(void);


/*
 * all white
 */
void WS_White(void);

#endif // BB_WS2812B_Headder_H
/**
 End of File
*/

