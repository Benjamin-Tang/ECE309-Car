//------------------------------------------------------------------------------
//  File name : switch.c
//  Description: This file  identifies by polling if a switch is pressed and 
//  changes the LCD contents that are displayed at the moment the switch is 
//  pressed. In main, a function call "Switches_Process();" transfers control 
//  to that function that is to be moved to switch.c. 
//
//  Author: Benjamin Tang  
//  Date: Nov 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

//Globals
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;

//Macros
// L_SPACE_1               (1)                   
// L_SPACE_2               (2)
// L_SPACE_3               (3)
// L_SPACE_4               (4)


//Display Process
void Display_Process(void){
  //============================================================================
  // Function name: Display_Process
  //
  // Description: This function controls the display process btwn display1-4.
  // 
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Global Variables
  //extern char *display_1;
  //extern char *display_2;
  //extern char *display_3;
  //extern char *display_4;
  //extern char posL1;
  //extern char posL2;
  //extern char posL3;
  //extern char posL4;
  //
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  ClrDisplay();
  lcd_out(display_1, LCD_HOME_L1, posL1);
  lcd_out(display_2, LCD_HOME_L2, posL2);
  lcd_out(display_3, LCD_HOME_L3, posL3);
  lcd_out(display_4, LCD_HOME_L4, posL4);
}
