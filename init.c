//------------------------------------------------------------------------------
//  File name : init.c
//  Description: This file contains the Initializations Configurations
//
//
//  Author: Benjamin Tang  
//  Date: Sept 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

//Global Variables
extern char display_line_1[CHAR_SIZE_11];
extern char display_line_2[CHAR_SIZE_11];
extern char display_line_3[CHAR_SIZE_11];
extern char display_line_4[CHAR_SIZE_11];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;

//============================================================================
//Function name: Init_Conditions
//
//Description: This function contains the initializations configurations of
//the system. Interrupts are disabled by default, they will need to be enable.
// 
//Passed : no variables passed
//Locals: no variables declared
//Returned: no values returned
//
//Global Variables
//extern char display_line_1[CHAR_SIZE_11];
//extern char display_line_2[CHAR_SIZE_11];
//extern char display_line_3[CHAR_SIZE_11];
//extern char display_line_4[CHAR_SIZE_11];
//extern char *display_1;
//extern char *display_2;
//extern char *display_3;
//extern char *display_4;
  
//Macros
//CHAR_SIZE_0             (0)
//
//Benjamin Tang  
//Date: Sept 2016
//Built with IAR Embedded Workbench Version: 6.50.1
//============================================================================
void Init_Conditions(void){  
  enable_interrupts();
  display_1 = &display_line_1[CHAR_SIZE_0];
  display_2 = &display_line_2[CHAR_SIZE_0];
  display_3 = &display_line_3[CHAR_SIZE_0];
  display_4 = &display_line_4[CHAR_SIZE_0];
}
//------------------------------------------------------------------------------
