//==============================================================================
//  File name: move.c
//  Description: This file contains the functions that are used to move the car
//               forward and backward.
//
//  Benjamin Tang
//  Sep 2016
//  Built with IAR Embedded Workbench Version: V7.4.2.4369 (6.50.1)
//==============================================================================

#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void right_stop(void) {
  TB1CCR1 = RESET;
  TB2CCR1 = RESET;
}

void left_stop(void) {
  TB1CCR2 = RESET;
  TB2CCR2 = RESET;
}

void right_forward(int right_forward_rate) {
  TB2CCR1 = RESET;
  TB1CCR1 = right_forward_rate;
}

void left_forward(int left_forward_rate) {
  TB2CCR2 = RESET;
  TB1CCR2 = left_forward_rate;
}

void right_reverse(int right_reverse_rate) {
  TB1CCR1 = RESET;
  TB2CCR1 = right_reverse_rate;
}

void left_reverse(int left_reverse_rate) {
  TB1CCR2 = RESET;
  TB2CCR2 = left_reverse_rate;
}

