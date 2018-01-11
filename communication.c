//------------------------------------------------------------------------------
//  File name : communication.c
//  Description: This file contains the code structure to send and recieve data
//               from my team members.
//
//
//  Author: Benjamin Tang  
//  Date: Nov 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"


// Globals
int valueFromTeam;
char *pointerValueFromTeam;
extern volatile unsigned int iot_rx_ring_wr;
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern char *display_1;
extern char adc_char[CHAR_ARRAY_SIZE];

void receiveFromTeam(void){
  //============================================================================
  // Function name: receiveFromTeam
  //
  // Description: This function contains structure to receive an integer from my
  //    team member properly, by storing the lower order followed by the higher
  //    order of the bit recieved, then displaying the value
  //
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  pointerValueFromTeam = (char*) &valueFromTeam;
  *pointerValueFromTeam = IOT_Char_Rx[COUNTZERO]; // Recaive lower order of integer
  pointerValueFromTeam++;
  *pointerValueFromTeam = IOT_Char_Rx[COUNTERONE]; // Recieve higher order of integer
  pointerValueFromTeam = (char*) &valueFromTeam;
  valueFromTeam++;
  HEXtoBCD(valueFromTeam);
  iot_rx_ring_wr -= COUNTERTWO;
  display_1[COUNTZERO] = adc_char[COUNTZERO];
  display_1[COUNTERONE] = adc_char[COUNTERONE];
  display_1[COUNTERTWO] = adc_char[COUNTERTWO];
  display_1[COUNTTHREE] = adc_char[COUNTTHREE];
  display_1[COUNTFOUR] = COUNTZERO;
  Display_Process();
  // Delay 
         waitForSeconds(COUNTERONE);

  
      // Send
  while(!(UCA1IFG & UCTXIFG)); // wait until not sending
  UCA1TXBUF = *pointerValueFromTeam; // Send low bit
  pointerValueFromTeam++; // increment pointer
  while(!(UCA1IFG & UCTXIFG)); // wait until not sending
  UCA1TXBUF = *pointerValueFromTeam; // send high bit
    //--------------------------------------------------------------------------
}

void startSendToTeam(void){
  //============================================================================
  // Function name: startSendToTeam
  //
  // Description: This function contains structure to send the first integer to 
  //    my team members properly, by incrementing my received value, and then 
  //    sending it to the next team member
  //
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  while(!(UCA1IFG & UCTXIFG));
  UCA1TXBUF = HEX01;
  while(!(UCA1IFG & UCTXIFG));
  UCA1TXBUF = HEX00;
  
  
  //----------------------------------------------------------------------------
}

