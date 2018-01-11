#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern char adc_char_L[CHAR_ARRAY_SIZE];
extern char adc_char_R[CHAR_ARRAY_SIZE];
extern unsigned int R_Det_Calib_White;
extern unsigned int L_Det_Calib_White;
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int R_Det_Uncalibrated;
extern volatile unsigned int L_Det_Uncalibrated;
extern char *display_2;
extern char *display_3;
extern volatile unsigned int twohunmsec_counter;

void HEXtoBCD_L_Det_Uncalibrated(int);
void HEXtoBCD_R_Det_Uncalibrated(int);
void HEXtoBCD_Thumb(int);

//===========================================================================
// Function name: ADC_Process
//
// Description: This function contains the ADC Process.
// Passed : no variables passed
// Locals: no variables declared
// Returned: no values returned
// Globals: none
//
// Author: Benjamin Tang
// Date: Oct 2016
// Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
//===========================================================================
void ADC_Process(){
  while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
  ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start
  
  HEXtoBCD_Thumb(ADC_Thumb);
  HEXtoBCD_R_Det_Uncalibrated(R_Det_Uncalibrated-R_Det_Calib_White);
  HEXtoBCD_L_Det_Uncalibrated(L_Det_Uncalibrated-L_Det_Calib_White);
  
  display_2 = adc_char_L;
  display_3 = adc_char_R;
}