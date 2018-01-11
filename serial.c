//------------------------------------------------------------------------------
//  File name : serial.c
//  Description: This file contains the serial communication code configurations
//
//
//  Author: Benjamin Tang  
//  Date: Sept. 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"


unsigned int temp;
volatile unsigned char USB_Char_Rx[SMALL_RING_SIZE];
volatile unsigned char USB_Char_Tx[SMALL_RING_SIZE];

unsigned volatile int usb_rx_ring_wr;
unsigned int usb_rx_ring_rd;
unsigned volatile int usb_tx_ring_wr;
unsigned volatile int usb_tx_ring_rd;

volatile char IOT_Char_Rx[SMALL_RING_SIZE];
volatile char IOT_Char_Tx[SMALL_RING_SIZE];

unsigned volatile int iot_rx_ring_wr;
unsigned int iot_rx_ring_rd;
unsigned volatile int iot_tx_ring_wr;
unsigned volatile int iot_tx_ring_rd;

volatile char  transmit_2_pc_ok = RESET;

unsigned int baudrate;
int calcNumber;
int calcHex;

extern unsigned int temp;
extern volatile unsigned  char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile unsigned char USB_Char_Tx[SMALL_RING_SIZE];

extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Tx[SMALL_RING_SIZE];

extern unsigned int oneSecCount;
extern int valueFromTeam;
extern char *pointerValueFromTeam;
extern int valueToTeam;
extern int *pointerValueToTeam;
extern int valueRecievedToDisplay[COUNTTHREE];
extern char hexSignal[COUNTEIGHT];

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
  //----------------------------------------------------------------------------
  unsigned int temp; 
  switch(__even_in_range(UCA0IV,HEX08)){
  case COUNTZERO:                       // Vector 0 - no interrupt
    break;
  case COUNTERTWO:                        // Vector 2 – RXIFG
    // code for Receive
    transmit_2_pc_ok = 1;
    temp = usb_rx_ring_wr;
    USB_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
    if (++usb_rx_ring_wr >= (SMALL_RING_SIZE)){
      usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    }
    break;
  case COUNTFOUR:                       // Vector 4 – TXIFG
    break;
  default: break;
  } 
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------ 

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void){
  unsigned int temp; 
  switch(__even_in_range(UCA1IV,HEX08)){
  case COUNTZERO: // Vector 0 - no interrupt
    break;
  case COUNTERTWO: // Vector 2 - RXIFG
    temp = iot_rx_ring_wr;
    IOT_Char_Rx[temp] = UCA1RXBUF; // TX -> IOT_Char_Tx character
    
    // stuff here is placing the received value in the receiver buffer
    if(transmit_2_pc_ok == 1){
      UCA0TXBUF = IOT_Char_Rx[temp];     // TX -> RXed character
    }
    
    if (++iot_rx_ring_wr >= (SMALL_RING_SIZE)){
      iot_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
    } 
    break;
  case COUNTFOUR: // Vector 4 TXIFG
   // UCA1TXBUF = hexSignal[temp2] ; // TX -> USB_Char_Tx character
//    if(transmit_2_pc_ok == 1){
//      if (++iot_tx_ring_wr >= (COUNTEIGHT)){
//        iot_tx_ring_wr = BEGINNING; // Circular buffer back to beginning
//      } 
//    }
    break;
  default: break;
  }
}

//------------------------------------------------------------------------------ 
void Init_Serial_UCA0(int calcNumber, int calcHex){
  int i;
  transmit_2_pc_ok = RESET;
  for(i=COUNTZERO; i<SMALL_RING_SIZE; i++){
    USB_Char_Rx[i] = HEX00; // USB Rx Buffer
  }
  usb_rx_ring_wr = BEGINNING;
  usb_rx_ring_rd = BEGINNING;
  
  for(i=COUNTZERO; i<LARGE_RING_SIZE; i++){
    USB_Char_Tx[i] = HEX00; // USB Tx Buffer
  }
  usb_tx_ring_wr = BEGINNING;
  usb_tx_ring_rd = BEGINNING;
  
  // Configure UART 0
  UCA0CTLW0 = COUNTZERO; // Use word register
  UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA0CTLW0 |= UCSWRST; // Set Software reset enable
  // 9,600 Baud Rate
  // 1. Calculate N = fBRCLK / Baudrate
  // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
  // if N > 16 continue with step 3, otherwise with step 2
  // 2. OS16 = 0, UCBRx = INT(N)
  // continue with step 4
  // 3. OS16 = 1,
  // UCx = INT(N/16),
  // = INT(N/16) = 833.333/16 => 52
  // UCFx = INT([(N/16) ñ INT(N/16)] ? 16)
  // = ([833.333/16-INT(833.333/16)]*16)
  // = (52.08333333-52)*16
  //  = 0.083*16 = 1
  // 4. UCSx is found by looking up the fractional part of N ?? N-INT(N)) in table Table 18-4
  // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
  // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  UCA0BRW = calcNumber; // 9,600 Baud
  // UCA0MCTLW = UCSx concatenate UCFx concatenate UCOS16;
  // UCA0MCTLW = 0x49 concatenate 1 concatenate 1;
  UCA0MCTLW = calcHex;
  UCA0CTL1 &= ~UCSWRST; // Release from reset
  UCA0IE |= UCRXIE; // Enable RX interrupt
  UCA0IE &= ~UCTXIE; // Disable RX interrupt
}

//------------------------------------------------------------------------------ 
void Init_Serial_UCA1(int calcNumber, int calcHex){
  int i;
  transmit_2_pc_ok = RESET;
  for(i=COUNTZERO; i<SMALL_RING_SIZE; i++){
    IOT_Char_Rx[i] = HEX00; // USB/IOT Rx Buffer
  }
  iot_rx_ring_wr = BEGINNING;
  iot_rx_ring_rd = BEGINNING;
  
  for(i=COUNTZERO; i<LARGE_RING_SIZE; i++){
    IOT_Char_Tx[i] = HEX00; // USB/IOT Tx Buffer
  }
  iot_tx_ring_wr = BEGINNING;
  iot_tx_ring_rd = BEGINNING;  
  
  // Configure UART 1
  UCA1CTLW0 = COUNTZERO; // Use word register
  UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
  UCA1CTLW0 |= UCSWRST; // Set Software reset enable
  // 9,600 Baud Rate
  // 1. Calculate N = fBRCLK / Baudrate
  // N = SMCLK / 9,600 => 8,000,000 / 9,600 = 833.3333333
  // if N > 16 continue with step 3, otherwise with step 2
  // 2. OS16 = 0, UCBRx = INT(N)
  // continue with step 4
  // 3. OS16 = 1,
  // UCx = INT(N/16),
  // = INT(N/16) = 833.333/16 => 52
  // UCFx = INT([(N/16) ñ INT(N/16)] ? 16)
  // = ([833.333/16-INT(833.333/16)]*16)
  //= (52.08333333-52)*16
  //  = 0.083*16 = 1
  // 4. UCSx is found by looking up the fractional part of N ?? N-INT(N)) in table Table 18-4
  // Decimal of SMCLK / 8,000,000 / 9,600 = 833.3333333 => 0.333 yields 0x49 [Table]
  // 5. If OS16 = 0 was chosen, a detailed error calculation is recommended to be performed
  // TX error (%) RX error (%)
  // BRCLK Baudrate UCOS16 UCBRx UCFx UCSx neg pos neg pos
  // 8000000 9600 1 52 1 0x49 -0.08 0.04 -0.10 0.14
  
  UCA1BRW = calcNumber; // 9,600 Baud
  // UCA1MCTLW = UCSx concatenate UCFx concatenate UCOS16;
  // UCA1MCTLW = 0x49 concatenate 1 concatenate 1;
  UCA1MCTLW = calcHex;
  UCA1CTL1 &= ~UCSWRST; // Release from reset
  UCA1IE |= UCRXIE; // Enable RX interrupt
  UCA1IE &= ~UCTXIE; // Disable TX interrupt
}


void out_character(char character){
  while (!(UCA1IFG & UCTXIFG));
  UCA1TXBUF = character;
}
