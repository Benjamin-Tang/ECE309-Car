//------------------------------------------------------------------------------
// File Name : shapes.c
// Description: This file contains the code function for shape paths of the car 
//
// Author: Benjamin Tang  
// Date: Sept 2016
// Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------


//MACROS========================================================================
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"
#include  "globals.h"

//Globals
extern char start_moving;
extern unsigned int moving;
extern volatile unsigned int Time_Sequence;

extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;

extern int cycles;
extern int i;
extern int loop;
extern int next_shape;


//Time for Paths
void wait10(unsigned int usec){
  //============================================================================
  // Function name: wait10
  //
  // Description: This function creates delayes for wheel on/off functions
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: no global variables
  //
  // Call Function wait10();
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //----------------------------------------------------------------------------
  // At the current clock rate this yields about 10usec per value passed
  // A value of  0 yields 1.37 uSec
  // A value of  1 yields 1.87 uSec
  // A value of  2 yields 2.36 uSec
  // A value of  3 yields 2.86 uSec
  // A value of  4 yields 3.36 uSec
  // A value of  5 yields 3.86 uSec
  // A value of  6 yields 4.36 uSec
  // A value of  7 yields 4.85 uSec
  // A value of  8 yields 5.354 uSec
  // A value of  9 yields 5.854 uSec
  // A value of 10 yields 6.353 uSec
  // A value of 11 yields 6.851 uSec
  // A value of 12 yields 7.351 uSec
  // A value of 13 yields 7.849 uSec
  // A value of 14 yields 8.350 uSec
  // A value of 15 yields 8.849 uSec
  // A value of 16 yields 9.342 uSec
  // A value of 17 yields 9.84 uSec
  // A value of 18 yields 10.34 uSec
  // A value of 19 yields 10.84 uSec
  //----------------------------------------------------------------------------
  //============================================================================
  
  int i,j;
  for(j=RESETZERO;j<usec;j++){
    for(i=RESETZERO;i<COUNTFOURTEEN;i++);
  }  
}

// Path Shapes
void circle_path(void){
  //============================================================================
  // Function name: circle_path
  //
  // Description: This function moves the car 2 complete circles (left turn)
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: no global variables
  //
  // Call Function circle_path();
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  while (cycles<MSEC100){
    right_forward_on();
    cycles++;
    left_forward_on();
    wait10(MSEC400);
    left_forward_off();
    wait10(MSEC5000);
    left_forward_on();
  }
  stop();
  cycles = RESETZERO;
}

void eight_path(void){
  //============================================================================
  // Function name: eight_path
  //
  // Description: This function moves the car in the shape of a figure 8
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: no global variables
  //
  // Call Function eight_path();
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  short_forward();
  cycles = RESETZERO;
  while (cycles<COUNTTHIRTYFIVE){
    right_forward_on();
    cycles++;
    left_forward_on();
    wait10(MSEC400);
    left_forward_off();
    wait10(MSEC5000);
    left_forward_on();
  }
  cycles = RESETZERO;
  short_forward();
  cycles = RESETZERO;
  while (cycles<COUNTFIFTY){
    left_forward_on();
    cycles++;
    right_forward_on();
    wait10(MSEC400);
    right_forward_off();
    wait10(MSEC5100);
    right_forward_on();
  }
  cycles = RESETZERO;
  short_forward();
  cycles = RESETZERO;
  while (cycles<COUNTFORTY){
    right_forward_on();
    cycles++;
    left_forward_on();
    wait10(MSEC400);
    left_forward_off();
    wait10(MSEC5000);
    left_forward_on();
  }
  cycles = RESETZERO;
  short_forward();
  cycles = RESETZERO;
  while (cycles<COUNTFIFTY){
    left_forward_on();
    cycles++;
    right_forward_on();
    wait10(MSEC400);
    right_forward_off();
    wait10(MSEC5100);
    right_forward_on();
  }
  cycles = RESETZERO;
  short_forward();
  stop();
  
  // Change to figure 8
  next_shape = FALSE;
}

void sharp_left_turn(void){
  //============================================================================
  // Function name: sharp_left_turn
  //
  // Description: This function moves the car in a sharp left turn
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: no global variables
  //
  // Call Function sharp_left_turn();
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  while (cycles<COUNTTWELVE){
    right_forward_on();
    cycles++;
    left_forward_on();
    wait10(MSEC400);
    left_forward_off();
    wait10(MSEC5000);
    left_forward_on();
  }
  stop();
  cycles = RESETZERO;
}

void triangle_path(void){
  //============================================================================
  // Function name: new_triangle_path
  //
  // Description: This function moves the car in the shape of a triangle
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: no global variables
  //
  // Call Function new_triangle_path();
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  wait10(MSEC50000);
  wait10(MSEC50000);
  wait10(MSEC50000);
  wait10(MSEC50000);
  
  loop=RESETZERO;
  while(loop < COUNTSIX){
    cycles = RESETZERO;
    short_forward();
    cycles = RESETZERO;
    wait10(MSEC50000);
    sharp_left_turn(); 
    cycles = RESETZERO;
    wait10(MSEC50000);
    loop++;
  }
  stop();
  cycles = RESETZERO;
  
  // Change to figure 8
  next_shape = TRUE;
}

void projFour(void){
  //============================================================================
  // Function name: projFour
  //
  // Description: This function moves the car forward one sec, reverse two secs, 
  // forward one sec, spin clockwise one sec, and spin counter-clockise one sec
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: no global variables
  //
  // Call Function projFour();
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  // Project 4 Motions
  wait10(MSEC60000);
  wait10(MSEC60000);
  wait10(MSEC60000);
  wait10(MSEC60000);
  
  display_1 = "Forward";
  posL3 = L_SPACE_2;
  display_2 = "Project04";
  posL2 = L_SPACE_1;
  display_3 = "ECE306";
  posL3 = L_SPACE_2;
  display_4 = "J Ndon";
  posL4 = L_SPACE_1;
  Display_Process();
  
  short_forward();
  stop();
  
  wait10(MSEC60000);
  wait10(MSEC60000);
  
  display_1 = "Reverse";
  posL3 = L_SPACE_2;
  display_2 = "Project04";
  posL2 = L_SPACE_1;
  display_3 = "ECE306";
  posL3 = L_SPACE_2;
  display_4 = "J Ndon";
  posL4 = L_SPACE_1;
  Display_Process();
  
  short_reverse();
  short_reverse();
  stop();
  
  
  wait10(MSEC60000);
  wait10(MSEC60000);
  
  display_1 = "Forward";
  posL3 = L_SPACE_2;
  display_2 = "Project04";
  posL2 = L_SPACE_1;
  display_3 = "ECE306";
  posL3 = L_SPACE_2;
  display_4 = "J Ndon";
  posL4 = L_SPACE_1;
  Display_Process();
  
  short_forward();
  stop();
  wait10(MSEC60000);
  wait10(MSEC60000);
  
  display_1 = "Clockwise";
  posL3 = L_SPACE_2;
  display_2 = "Project04";
  posL2 = L_SPACE_1;
  display_3 = "ECE306";
  posL3 = L_SPACE_2;
  display_4 = "J Ndon";
  posL4 = L_SPACE_1;
  Display_Process();
  
  clockwise();
  stop();
  wait10(MSEC60000);
  wait10(MSEC60000);
  
  display_1 = "Counter C";
  posL3 = L_SPACE_2;
  display_2 = "Project04";
  posL2 = L_SPACE_1;
  display_3 = "ECE306";
  posL3 = L_SPACE_2;
  display_4 = "J Ndon";
  posL4 = L_SPACE_1;
  Display_Process();
  
  counterClockwise();
  stop();
  wait10(MSEC60000);
  wait10(MSEC60000);
  
  display_1 = "END";
  posL3 = L_SPACE_2;
  display_2 = "Project04";
  posL2 = L_SPACE_1;
  display_3 = "ECE306";
  posL3 = L_SPACE_2;
  display_4 = "J Ndon";
  posL4 = L_SPACE_1;
  Display_Process();
  
  stop();
}

void clockwise(void){
  //============================================================================
  // Function name: clockwise
  //
  // Description: This function spins the car clockwise
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: no global variables
  //
  // Call Function clockwise();
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  //  
  //  while (cycles<MSEC1000){
  //    stop();
  //    right_reverse_on();
  //    left_forward_on();
  //    cycles++;
  //    wait10(COUNTFORTY);
  //  }
  //  stop();
  //  cycles = RESETZERO;
  
  right_reverse_on();
  left_forward_on();
  
  
}

void counterClockwise(void){
  //============================================================================
  // Function name: counterClockwise
  //
  // Description: This function spins the car Counter-Clockwise
  //
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: no global variables
  //
  // Call Function counterClockwise();
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  //  
  //  while (cycles<MSEC1000){
  //    stop();
  //    left_reverse_on();
  //    right_forward_on();
  //    cycles++;
  //    wait10(COUNTFORTY);
  //  }
  //  stop();
  //  cycles = RESETZERO;
  
  left_reverse_on();
  right_forward_on();
}
