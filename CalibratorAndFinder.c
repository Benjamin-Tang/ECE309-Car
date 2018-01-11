#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern unsigned int R_Det_Calib_White;
extern unsigned int L_Det_Calib_White;
extern volatile unsigned int R_Det_Uncalibrated;
extern volatile unsigned int L_Det_Uncalibrated;
extern unsigned int Interception_Flag;
extern char *display_4;
unsigned int R_Det_Calib_Black;
unsigned int L_Det_Calib_Black;
unsigned int line_int_toggle;
void right_stop(void);
void left_stop(void);
void right_forward(int);
void left_forward(int);
void right_reverse(int);
void left_reverse(int);


//===========================================================================
// Function name: Calibrator_and_Finder.c
//
// Description: This function contains the while loop that runs continuously
// to calibrate the non-line area value and the line area value. The function
// also allows the car to move forward until it intercepts a black line.
//
// Passed : no variables passed
// Locals: unsigned int R_Det_Calib_Black;
//         unsigned int L_Det_Calib_Black;
// Returned: Calibrated_Line
// Globals: extern unsigned int R_Det_Calib_White;
//          extern unsigned int L_Det_Calib_White;
//          extern volatile unsigned int R_Det_Uncalibrated;
//          extern volatile unsigned int L_Det_Uncalibrated;
//          extern unsigned int Interception_Flag;
//          extern char *display_4;
//
// Author: Benjamin Tang
// Date: Oct 2016
// Compiler: Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
//===========================================================================

int Calibrator_and_Finder (void){
  while(Interception_Flag == FIRST_FLAG){
    if(R_Det_Uncalibrated-R_Det_Calib_White > PREEMPTIVE_LINE_VAL 
       && L_Det_Uncalibrated-L_Det_Calib_White > PREEMPTIVE_LINE_VAL 
         && Interception_Flag == FIRST_FLAG){
           for(int i = RESET; i < INTERCEPT_STOP; i++){
             for(int j = RESET; j < INTERCEPT_STOP; j++){
               right_stop();
               left_stop();
               R_Det_Calib_Black = R_Det_Uncalibrated-R_Det_Calib_White;
               L_Det_Calib_Black = L_Det_Uncalibrated-L_Det_Calib_White;
             }
           }
           for(int i = RESET; i < INTERCEPT_REV; i++){
             for(int j = RESET; j < INTERCEPT_REV; j++){
               right_reverse(MED);
               left_reverse(MED_FAST);
               display_4 = "Reverse";
             }
           }
           for(int i = RESET; i < INTERCEPT_STOP2; i++){
             for(int j = RESET; j < INTERCEPT_STOP2; j++){
               display_4 = "Stop";
               right_stop();
               left_stop();
             }
           }
           for(int i = RESET; i < INTERCEPT_PIVOT; i++){
             for(int j = RESET; j < INTERCEPT_PIVOT; j++){
               right_forward(MED);
               left_reverse(MED_FAST);
             }
           }
           display_4 = "Follow!";
           right_stop();
           left_stop();
           Display_Process();
           Interception_Flag = FUTURE_FLAGGER ;
           break;
         }
  }
  return (R_Det_Calib_Black + L_Det_Calib_Black)/AVG_DIVISOR;
}