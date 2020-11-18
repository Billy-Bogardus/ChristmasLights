/*
 * File:   BitBangWS2812b.c
 * Author: Bill
 *
 * Created on October 21, 2019, 3:56 PM
 */

#include "BitBangWS2812b.h"

void WS_dim(int A, int B, int C, int brightness)
{
    if( brightness > 0 && brightness <=8)//decrease brightness from 0 - 100%
    {
        A = A >> brightness;
        B = B >> brightness;
        C = C >> brightness;
    }
    WS_Word(A, B, C);
}

void WS_Word(int A,int B,int C)
{
   //order received is red green and blue
   //Below is the order we need to send the bytes. However, it needs to be sent most significant bit first
   ///Green B   Red A     Blue C
   ///0      7  8     15 16     23      
   ///01234567  01234567  01234567
    
    int Bx = 0;
    for(int i=23; i!=-1; i--)
    {
        if(i>15)//send Red bit
        {
            int x = i - 16;
            Bx = 1 & ( A >> x );
        }
        else if ( i > 7 )//send Green bit
        {
            int x = i - 8;
            Bx = 0b00000001 & ( B >> x );
        }
        else if ( i >= 0 )//send Red bit
        {
            int x = i;
            Bx = 0b00000001 & ( C >> x );
        }
        else //the code has broken, send a one
        {
            Bx = 1;
        }
        WS_Write(Bx);//write a bit
    }        
}


void WS_Write( int A )
{
    if(A)//send a 1
    {
        LATAbits.LATA2 = 1;//must stay high >0.35us
        NOP();
        NOP();
        NOP();
        LATAbits.LATA2 = 0;
    }
    else //send a 0
    {
        LATAbits.LATA2 = 1;//must stay high <0.35us
        LATAbits.LATA2 = 0;
        //NOP();//These NOP statements are not really needed for the WS2812 to work.
        //NOP();
        //NOP();
    }
    
}

void WSTest(int length, int brightness)
{
    
    for(int i = 0; i<length; i++)
    {
        WS_Word(0x00, 0x00, 0x00); //off
    }
    __delay_ms(WSReset);
    __delay_ms(250);
    int b =0;
    for(b = 0; b<length-6; b+=6 )
    {
        WS_dim(0xFF, 0x00, 0x00, brightness); //Red
        WS_dim(0xFF, 0xFF, 0x00, brightness); //Yellow
        WS_dim(0x00, 0xFF, 0x00, brightness); //Green
        WS_dim(0x00, 0xFF, 0xFF, brightness); //Cyan
        WS_dim(0x00, 0x00, 0xFF, brightness); //Blue
        WS_dim(0xFF, 0x00, 0xFF, brightness); //Magenta
    }
    while(b < length)
    {
        WS_dim(0xFF, 0x00, 0x00, brightness); //Red
        b++;
        if(b == length) break;
        WS_dim(0xFF, 0xFF, 0x00, brightness); //Yellow
        b++;
        if(b == length) break;
        WS_dim(0x00, 0xFF, 0x00, brightness); //Green
        b++;
        if(b == length) break;
        WS_dim(0x00, 0xFF, 0xFF, brightness); //Cyan
        b++;
        if(b == length) break;
        WS_dim(0x00, 0x00, 0xFF, brightness); //Blue
        b++;
        if(b == length) break;
        WS_dim(0xFF, 0x00, 0xFF, brightness); //Magenta
        b++;
        if(b == length) break;
    }
    
    __delay_ms(WSReset);
    __delay_ms(250);
}
//WSLoop function for bitbanging WS2812B controlls
void WSLoop(void)
{
    int i = 0;
    GIE = 0;
    for(i = 0; i<=10; i++)
    {
        WS_Word(0xFF, 0x00, 0x00); //Red
        WS_Word(0x00, 0x09, 0x00); //Green
        WS_Word(0x00, 0x00, 0x09); //Blue
        WS_Word(0x09, 0x09, 0x00); //Yellow
        WS_Word(0x09, 0x00, 0x09); //Magenta
        WS_Word(0x00, 0x09, 0x09); //Cyan
    }
    
    __delay_ms(WSReset);
    __delay_ms(250);
    
    for(i = 0; i<=10; i++)
    {
        WS_Word(0x00, 0x09, 0x09); //Cyan
        WS_Word(0xFF, 0x00, 0x00); //Red
        WS_Word(0x00, 0x09, 0x00); //Green
        WS_Word(0x00, 0x00, 0x09); //Blue
        WS_Word(0x09, 0x09, 0x00); //Yellow
        WS_Word(0x09, 0x00, 0x09); //Magenta
    }
    
    __delay_ms(WSReset);
    __delay_ms(250);
    
    
    for(i = 0; i<=10; i++)
    {
        WS_Word(0x09, 0x00, 0x09); //Magenta
        WS_Word(0x00, 0x09, 0x09); //Cyan
        WS_Word(0xFF, 0x00, 0x00); //Red
        WS_Word(0x00, 0x09, 0x00); //Green
        WS_Word(0x00, 0x00, 0x09); //Blue
        WS_Word(0x09, 0x09, 0x00); //Yellow
    }
    
    __delay_ms(WSReset);
    __delay_ms(250);
    
    
    for(i = 0; i<=10; i++)
    {
        WS_Word(0x09, 0x09, 0x00); //Yellow
        WS_Word(0x09, 0x00, 0x09); //Magenta
        WS_Word(0x00, 0x09, 0x09); //Cyan
        WS_Word(0xFF, 0x00, 0x00); //Red
        WS_Word(0x00, 0x09, 0x00); //Green
        WS_Word(0x00, 0x00, 0x09); //Blue
    }
    
    __delay_ms(WSReset);
    __delay_ms(250);
    
    for(i = 0; i<=10; i++)
    {
        WS_Word(0x00, 0x00, 0x09); //Blue
        WS_Word(0x09, 0x09, 0x00); //Yellow
        WS_Word(0x09, 0x00, 0x09); //Magenta
        WS_Word(0x00, 0x09, 0x09); //Cyan
        WS_Word(0xFF, 0x00, 0x00); //Red
        WS_Word(0x00, 0x09, 0x00); //Green
        WS_Word(0x00, 0x00, 0x09); //Blue
    }
    
    __delay_ms(WSReset);
    __delay_ms(250);
    
    
    for(i = 0; i<=10; i++)
    {
        WS_Word(0x00, 0x09, 0x00); //Green
        WS_Word(0x00, 0x00, 0x09); //Blue
        WS_Word(0x09, 0x09, 0x00); //Yellow
        WS_Word(0x09, 0x00, 0x09); //Magenta
        WS_Word(0x00, 0x09, 0x09); //Cyan
        WS_Word(0xFF, 0x00, 0x00); //Red
    }
    
    __delay_ms(WSReset);
    __delay_ms(250);
    
    
    GIE =1;
    
}

void WS_White(void)
{
    GIE = 0;
    
    WS_Word(0xff, 0xff, 0xff); //white
    WS_Word(0xff, 0xff, 0xff); //white
    WS_Word(0xff, 0xff, 0xff); //white
    
    WS_Word(0xff, 0xff, 0xff); //white
    WS_Word(0xff, 0xff, 0xff); //white
    WS_Word(0xff, 0xff, 0xff); //white
    
    __delay_ms(WSReset);
}