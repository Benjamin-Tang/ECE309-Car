#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

volatile unsigned int ADC_Thumb;
volatile unsigned int Channel_Counter;
volatile unsigned int R_Det_Uncalibrated;
volatile unsigned int L_Det_Uncalibrated;
//===========================================================================
// Function name: ADC10_ISR
//
// Description: This function contains the interrupt service routine for the
//              ADC - in particular, for the (thingy thing) for the ADC.
//
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: char* display_1
// char* display_2
// slow_input_down
// control_state[CNTL_STATE_INDEX]
//
// Author: Benjamin Tang
// Date: Oct 2016
// Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
//===========================================================================
//------------------------------------------------------------------------------
// ADC10 interrupt service routine
// ADC_Right_Detector;  // A00 ADC10INCH_0 - P1.0
// ADC_Left_Detector;   // A01 ADC10INCH_1 - P1.1
// ADC_Thumb;           // A03 ADC10INCH_3 - P1.3
// ADC_Temp;            // A10 ADC10INCH_10 – Temperature REF module
// ADC_Bat;             // A11 ADC10INCH_11 - Internal
#pragma vector=ADC10_VECTOR

__interrupt void ADC10_ISR(void){
switch(__even_in_range(ADC10IV,12)) {
case 0: break;          // No interrupt
case 2: break;          // conversion result overflow
case 4: break;          // conversion time overflow
case 6: break;          // ADC10HI
case 8: break;          // ADC10LO
case 10: break;         // ADC10IN
case 12:
ADC_Thumb = ADC10MEM0;  // Channel A3
// Need this to change the ADC10INCH_x value.
 ADC10CTL0 &= ~ADC10ENC; // Turn off the ENC bit of the ADC10CTL0
 switch (Channel_Counter){
 case 0:
 ADC10MCTL0 = ADC10INCH_1; // Next channel A1
 R_Det_Uncalibrated = ADC10MEM0; // Insert Current Channel result for A0
 Channel_Counter++;
 break;
 case 1:
 ADC10MCTL0 = ADC10INCH_3; // Next channel A3 - thumbwheel
 L_Det_Uncalibrated = ADC10MEM0; // Current Channel result for A1
 Channel_Counter++;
 break;
 case 2:
 ADC10MCTL0 = ADC10INCH_0; // Next channel A0
 ADC_Thumb = ADC10MEM0; // Current Channel result for A3
 Channel_Counter = 0;
 break;
 default:
 break;
}
ADC10CTL0 |= ADC10ENC; // Turn on the ENC bit of the ADC10CTL0
ADC10CTL0 |= ADC10SC; // Start next sample.
break;

break;
default: break;
}
}