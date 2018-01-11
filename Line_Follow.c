#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

extern volatile unsigned int interrupt_count;
unsigned int one_sec_incrementer = RESET;
extern char adc_char_L[CHAR_ARRAY_SIZE];
extern char adc_char_R[CHAR_ARRAY_SIZE];
extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int R_Det_Uncalibrated;
extern volatile unsigned int L_Det_Uncalibrated;
extern unsigned int right_forward_rate;
extern unsigned int left_forward_rate;
extern unsigned int right_reverse_rate;
extern unsigned int left_reverse_rate;
unsigned int Interception_Flag;
unsigned int R_Det_Calib_White;
unsigned int L_Det_Calib_White;
unsigned int Current_R_Value;
unsigned int Current_L_Value;
unsigned int Stuck_Count;
unsigned int Calibrated_Line;
extern unsigned int line_int_toggle;
extern unsigned int follow_toggle;
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
void ADC_Process();
void Init_ADC(void);
void right_stop(void);
void left_stop(void);
void right_forward(int);
void left_forward(int);
void right_reverse(int);
void left_reverse(int);
int Calibrator_and_Finder(void);
void command_menu(void);


void Line_Follow (void){
  
  while(follow_toggle){
    ADC_Process();
    if (line_int_toggle){
      P3OUT |= IR_LED;
      display_1 = "IR ON";
      R_Det_Calib_White = R_Det_Uncalibrated - MANUAL_OFFSET;
      L_Det_Calib_White = L_Det_Uncalibrated - MANUAL_OFFSET;
      right_forward(MED);
      left_forward(FAST);
      display_4 = "Intercept";
      Interception_Flag = FIRST_FLAG;
      Calibrated_Line = Calibrator_and_Finder();
      line_int_toggle = RESET;
    }
    
    if(Interception_Flag == FUTURE_FLAGGER){
      Current_R_Value = R_Det_Uncalibrated-R_Det_Calib_White;
      Current_L_Value = L_Det_Uncalibrated-L_Det_Calib_White;
      if(Current_R_Value < Calibrated_Line-R_Det_Calib_White
         && Current_R_Value > R_Det_Calib_White){
           left_forward(MED);
           right_forward(MED_FAST);
         }
      else if(Current_L_Value < Calibrated_Line-L_Det_Calib_White
              && Current_L_Value > L_Det_Calib_White){
                left_forward(MED_FAST);
                right_forward(SLOW_MED);
              }
      else if(Current_L_Value < L_Det_Calib_White 
              && Current_R_Value < R_Det_Calib_White){
                if(Current_L_Value < Current_R_Value){
                  left_reverse(MED);
                  right_reverse(SLOW);
                }
                else if(Current_R_Value < Current_L_Value){
                  left_reverse(SLOW);
                  right_reverse(MED);
                }
              }
      else{
        right_forward(MED_FAST);
        left_forward(MED_FAST);
      }
    }
    command_menu();
  }
}