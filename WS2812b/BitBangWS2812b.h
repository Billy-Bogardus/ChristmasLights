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

#define WSReset 0.280 //Time in milli Seconds
#define WSPulse0H 0.220
#define WSPulse0L 0.580
#define WSPulse1H 0.580
#define WSPulse1L 0.220
#define WSTotal 0.800
#define WSERROR 0.150

/**
#define WSReset 60.000 //Time in milli Seconds
#define WSPulse0H 0.400
#define WSPulse0L 0.850
#define WSPulse1H 0.800
#define WSPulse1L 0.450
#define WSTotal 1.250
#define WSERROR 0.150
**/
// declare variables



/**
 * 
 * @param A Red
 * @param B Green
 * @param C Blue
 * @Example
    WS_Word(0xff, 0x00, 0x00);
 */
void WS_dim(int A, int B, int C, int brightness);

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


void WSSlow(int lengh, int maxBrightness, int minBrightness);

void WS_RYGCBM(int length, int brightness);
/**
 * 
 */
void WSTest(int length, int brightness);

/**
 * 
 */
void WSLoop(void);


/*
 * all white
 */
void WS_White(int length, int brightness);

#endif // BB_WS2812B_Headder_H
/**
 End of File
*/

