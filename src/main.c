/* Copyright (C) 2015 Sergey Sharybin <sergey.vfx@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <pic18.h>
#include <pic18f4550.h>

#define _XTAL_FREQ 1000000

#pragma config PLLDIV   = 5         /* 20Mhz external oscillator */
#pragma config CPUDIV   = OSC1_PLL2
#pragma config USBDIV   = 2         /* Clock source from 96MHz PLL/2 */
#pragma config FOSC     = INTOSC_EC
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = ON
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
/* #pragma config CCP2MX   = ON */
#pragma config STVREN   = ON
#pragma config LVP      = OFF
/* #pragma config ICPRT    = OFF */
#pragma config XINST    = OFF
#pragma config CP0      = OFF
#pragma config CP1      = OFF
/* #pragma config CP2      = OFF */
/* #pragma config CP3      = OFF */
#pragma config CPB      = OFF
/* #pragma config CPD      = OFF */
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
/* #pragma config WRT2     = OFF */
/* #pragma config WRT3     = OFF */
#pragma config WRTB     = OFF
#pragma config WRTC     = OFF
/* #pragma config WRTD     = OFF */
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
/* #pragma config EBTR2    = OFF */
/* #pragma config EBTR3    = OFF */
#pragma config EBTRB    = OFF

#define RS  LATBbits.LB0
#define RW  LATBbits.LB1
#define E   LATBbits.LB2
#define CS1 LATEbits.LE2
#define CS2 LATEbits.LE1
#define RST LATEbits.LE0
#define D   LATD

unsigned char CS1_DATA[64][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 128, 1, 0, 0, 0, },
  {0, 0, 0, 128, 31, 0, 0, 0, },
  {0, 0, 0, 128, 255, 1, 0, 0, },
  {0, 0, 0, 0, 254, 15, 0, 0, },
  {0, 0, 0, 0, 224, 15, 0, 0, },
  {0, 0, 0, 0, 0, 14, 0, 0, },
  {0, 0, 0, 0, 224, 15, 0, 0, },
  {0, 252, 127, 0, 255, 1, 0, 0, },
  {0, 252, 127, 128, 31, 0, 0, 0, },
  {0, 252, 127, 128, 1, 0, 0, 0, },
  {0, 128, 1, 128, 31, 0, 0, 0, },
  {0, 128, 1, 0, 255, 1, 0, 0, },
  {0, 128, 1, 0, 224, 15, 0, 0, },
  {0, 128, 1, 0, 0, 14, 0, 0, },
  {0, 128, 1, 0, 224, 15, 0, 0, },
  {0, 128, 1, 0, 254, 15, 0, 0, },
  {0, 252, 127, 128, 255, 1, 0, 0, },
  {0, 252, 127, 128, 31, 0, 0, 0, },
  {0, 252, 127, 128, 1, 0, 0, 0, },
  {0, 0, 0, 0, 224, 1, 0, 0, },
  {0, 0, 0, 0, 248, 7, 0, 0, },
  {0, 0, 0, 0, 248, 7, 0, 0, },
  {0, 0, 15, 0, 28, 14, 0, 0, },
  {0, 192, 63, 0, 12, 12, 0, 0, },
  {0, 192, 63, 0, 12, 12, 0, 0, },
  {0, 224, 118, 0, 12, 12, 0, 0, },
  {0, 96, 102, 0, 28, 14, 0, 0, },
  {0, 96, 102, 0, 248, 7, 0, 0, },
  {0, 96, 102, 0, 248, 7, 0, 0, },
  {0, 224, 102, 0, 224, 1, 0, 0, },
  {0, 192, 103, 0, 0, 0, 0, 0, },
  {0, 192, 103, 0, 0, 0, 0, 0, },
  {0, 0, 55, 0, 252, 15, 0, 0, },
  {0, 0, 0, 0, 252, 15, 0, 0, },
  {0, 0, 0, 0, 252, 15, 0, 0, },
};

unsigned char CS2_DATA[64][8] = {
  {0, 254, 127, 0, 24, 0, 0, 0, },
  {0, 254, 127, 0, 12, 0, 0, 0, },
  {0, 254, 127, 0, 12, 0, 0, 0, },
  {0, 0, 0, 0, 12, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 254, 127, 192, 255, 15, 0, 0, },
  {0, 254, 127, 192, 255, 15, 0, 0, },
  {0, 254, 127, 192, 255, 15, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 15, 0, 224, 1, 0, 0, },
  {0, 192, 63, 0, 248, 7, 0, 0, },
  {0, 192, 63, 0, 252, 15, 0, 0, },
  {0, 224, 112, 0, 28, 14, 0, 0, },
  {0, 96, 96, 0, 12, 12, 0, 0, },
  {0, 96, 96, 0, 12, 12, 0, 0, },
  {0, 96, 96, 0, 8, 4, 0, 0, },
  {0, 224, 112, 0, 24, 6, 0, 0, },
  {0, 192, 63, 192, 255, 15, 0, 0, },
  {0, 192, 63, 192, 255, 15, 0, 0, },
  {0, 0, 15, 192, 255, 15, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 3, 0, 0, 0, 0, },
  {0, 0, 240, 3, 0, 0, 0, 0, },
  {0, 0, 240, 1, 0, 0, 0, 0, },
  {0, 0, 240, 128, 255, 14, 0, 0, },
  {0, 0, 0, 128, 255, 14, 0, 0, },
  {0, 0, 0, 128, 255, 14, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 0, },
};

void main(void) {
  //OSCCONbits.IRCF = 0b111;
  OSCCONbits.IRCF = 0b100;

  TRISA = 0b0000000;
  TRISB = 0b0000000;
  TRISC = 0b0000000;
  TRISD = 0b0000000;
  TRISE = 0b0000000;

  PORTA = 0b00000000;
  PORTB = 0b00000000;
  PORTC = 0b00000000;
  PORTD = 0b00000000;
  PORTE = 0b00000000;

  LATA = 0b00000000;
  LATB = 0b00000000;
  LATC = 0b00000000;
  LATD = 0b00000000;
  LATE = 0b00000000;

#define NOP asm(" nop")
#define LCD_PREPARE() { RST = 0; }
#define LCD_INIT() { RST = 1; RW = 1; E = 1; RS = 0; }
#define LCD_COMMAND(rs, rw, cs1, cs2, data) \
  {  \
    E = 0; RW = rw; RS = rs; CS1 = cs1; CS2 = cs2; D = data; E = 1; \
    NOP; NOP; NOP; NOP; \
    E = 0; NOP; NOP; NOP; NOP; RW = 1; RS = 0; D = 0b00000000; E = 1; NOP; NOP; NOP; NOP; \
  } (void)0
#define LCD_START(cs1, cs2, on) LCD_COMMAND(0, 0, cs1, cs2, (0b00111110 + on))
#define LCD_SET_Y(cs1, cs2, y) LCD_COMMAND(0, 0, cs1, cs2, (0b01000000 + y))
#define LCD_SET_X(cs1, cs2, x) LCD_COMMAND(0, 0, cs1, cs2, (0b10111000 + x))
#define LCD_SET_Z(cs1, cs2, z) LCD_COMMAND(0, 0, cs1, cs2, (0b11000000 + z))
//#define LCD_STATUS_READ(cs1, cs2) {  }  /* TODO(sergey): Needs implementation */
#define LCD_WRITE(cs1, cs2, data) LCD_COMMAND(1, 0, cs1, cs2, data)
//#define LCD_READ(cs1, cs2, data) LCD_COMMAND(1, 0, cs1, cs2, data)  /* TODO(sergey): Needs implementation */

  LCD_PREPARE();
  __delay_ms(50);
  LCD_INIT()

  /* Initialize */
  LCD_START(1, 0, 1);
  LCD_START(0, 1, 1);

  /* Set start line */
  LCD_SET_Z(1, 0, 0);
  LCD_SET_Z(0, 1, 0);

  while (1) {
    int a, b;
    for (b = 0; b < 8; ++b) {
      LCD_SET_X(1, 0, b);
      LCD_SET_Y(1, 0, 0);
      for (a = 0; a < 64; ++a) {
        LCD_WRITE(1, 0, CS1_DATA[a][b]);
      }
    }
    LCD_SET_Z(1, 0, 0);
    for (b = 0; b < 8; ++b) {
      LCD_SET_X(0, 1, b);
      LCD_SET_Y(0, 1, 0);
      for (a = 0; a < 64; ++a) {
        LCD_WRITE(0, 1, CS2_DATA[a][b]);
      }
    }
    LCD_SET_Z(0, 1, 0);
  }
}
