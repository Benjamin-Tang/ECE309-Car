//------------------------------------------------------------------------------
//  File name : adc.c
//  Description: This file contains the code implement the adc 
//  for display on an LCD or monitor 
//
//
//  Author: Benjamin Tang  
//  Date: Nov 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"


//ADC
volatile unsigned int channelToSwitchCount;
volatile unsigned int ADC_Right_Detector;
volatile unsigned int ADC_Left_Detector;
volatile unsigned int ADC_Thumb;
char displayCharRight[COUNTFIVE] = {COUNTZERO};
char displayCharLeft[COUNTFIVE] = {COUNTZERO};
char displayCharThumb[COUNTFIVE] = {COUNTZERO};

//------------------------------------------------------------------------------ 
// Configure ADC10_B
void Init_ADC(void){
    P3OUT |= IR_LED; //Turn on the IR LED
  ADC10CTL0 = RESET_STATE; // Clear ADC10CTL0
  ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
  ADC10CTL0 &= ~ADC10MSC; // Single Sequence
  ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled
  
  ADC10CTL1 = RESET_STATE; // Clear ADC10CTL1
  ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
  ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer 
  ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted. 
  ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
  ADC10CTL1 |= ADC10SSEL_0; // MODCLK
  ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
  
  ADC10CTL2 = RESET_STATE; // Clear ADC10CTL2
  ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
  ADC10CTL2 |= ADC10RES; // 10-bit resolution
  ADC10CTL2 &= ~ADC10DF; // Binary unsigned
  ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
  
  ADC10MCTL0 = RESET_STATE; // Clear ADC10MCTL0
  ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
  ADC10MCTL0 |= ADC10INCH_0; // Channel A0 Right Detect
  ADC10IE |= ADC10IE0;   // Enable ADC conversion complete interrupt 
  ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------ 
// ADC10 interrupt service routine
// ADC_Right_Detector; // A00 ADC10INCH_0 - P1.0
// ADC_Left_Detector; // A01 ADC10INCH_1 - P1.1
// ADC_Thumb; // A03 ADC10INCH_3 - P1.3
// ADC_Temp; // A10 ADC10INCH_10 – Temperature REF module
// ADC_Bat; // A11 ADC10INCH_11 - Internal
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
  switch(__even_in_range(ADC10IV,COUNTTWELVE)) {
  case COUNTZERO: break; // No interrupt
  case COUNTTWO: break; // conversion result overflow 
  case COUNTFOUR: break; // conversion time overflow
  case COUNTSIX: break; // ADC10HI
  case COUNTEIGHT: break; // ADC10LO
  case COUNTTEN: break; // ADC10IN
  case COUNTTWELVE:
          //display_1 = "12";
    //ADC_Thumb = ADC10MEM0; // Channel A3
    //break;
    //ADC10INCH_0 is for Channel A0 Which signal is connected to the A0 pin? 
    //ADC10INCH_1 is for Channel A1 Which signal is connected to the A1 pin? 
    //ADC10INCH_3 is for Channel A3 Which signal is connected to the A3 pin?
    // Need this to change the ADC10INCH_x value.
    ADC10CTL0 &= ~ADC10ENC; // Turn off the ENC bit of the ADC10CTL0
      TA0CCTL1 |= CCIE; // CCR1 enable interrupt;
    switch (channelToSwitchCount){
    case HEX00:
      ADC10MCTL0 = ADC10INCH_1; // Next channel A1
      ADC_Right_Detector = ADC10MEM0; // Current Channel result for A0 
      //displayRight(ADC_Right_Detector);
          //HEXtoBCD_Right(ADC_Right_Detector);
      channelToSwitchCount++;
      break;
    case HEX01:
      ADC10MCTL0 = ADC10INCH_3; // Next channel A3
      ADC_Left_Detector = ADC10MEM0; // Current Channel result for A1
      channelToSwitchCount++;
      break; 
    case HEX02:
      ADC10MCTL0 = ADC10INCH_0; // Next channel A0
      ADC_Thumb = ADC10MEM0; // Current Channel result for A3 Channel count value needs to be set back to 0;
      channelToSwitchCount = COUNTZERO;
      break;
    default: 
      break;
    }
    ADC10CTL0 |= ADC10ENC;  // Turn on the ENC bit of the ADC10CTL0
    ADC10CTL0 |= ADC10SC; // Start next sample.
    break;
  } 
}
//------------------------------------------------------------------------------


void ADC_Process(void){
  while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
  ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start 
}

//
//void displayRight(unsigned int input){
//  displayCharRight[0] = (input/1000) + char_offset;
//  displayCharRight[1] = (input/100)%10 + char_offset;
//  displayCharRight[2] = (input/10)%10 + char_offset;
//  displayCharRight[3] = (input%10)+ char_offset;
//}