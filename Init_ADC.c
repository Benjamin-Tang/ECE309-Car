//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

//===========================================================================
// Function name: Init_ADC
//
// Description: This function contains the initial configurations for the 
//              ADC and the ADC Prcoess function.
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: none
//
// Author: Benjamin Tang
// Date: Oct 2016
// Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
//===========================================================================
// Configure ADC10_B
void Init_ADC(void){
ADC10CTL0 = RESET; // Clear ADC10CTL0
ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
ADC10CTL0 &= ~ADC10MSC; // Single Sequence
ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled
ADC10CTL1 = RESET; // Clear ADC10CTL1
ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
ADC10CTL1 |= ADC10SSEL_0; // MODCLK
ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
ADC10CTL2 = RESET; // Clear ADC10CTL2
ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
ADC10CTL2 |= ADC10RES; // 10-bit resolution
ADC10CTL2 &= ~ADC10DF; // Binary unsigned
ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
ADC10MCTL0 = RESET; // Clear ADC10MCTL0
ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
ADC10MCTL0 |= ADC10INCH_3; // Channel A3 Thumb Wheel
ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt
}
//------------------------------------------------------------------------------