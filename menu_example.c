//------------------------------------------------------------------------------
//  File name : menu_example.c
//  Description: This file contains a sample menu routine -
//
//  Author: Benjamin Tang  
//  Date: Sept. 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "macros.h"
#include  "string.h"
#include  "functions.h"
//------------------------------------------------------------------------------

#define NO_CHARACTER         (0x00)   // No character available

//------------------------------------------------------------------------------
// Function Prototypes
void menu(void);
void grab_a_character(void);
int wait_for_character(void);
void menu_program(void);
void print_CR(void);
void outchar(char character);
void get_mac(void);
void increment_usb_rx_ring(void);
void increment_iot_rx_ring(void);
void out_wifi(char character);
void get_command(char* input_String);
void reset_command(char* input_String);
void waitForSeconds(int);
//------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
// Globals
extern volatile char transmit_2_pc_ok;
extern char menu_selection;
extern volatile unsigned char USB_Char_Rx[SMALL_RING_SIZE];// USB Character
extern volatile unsigned int usb_rx_ring_wr;
extern unsigned int usb_rx_ring_rd;
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Tx[SMALL_RING_SIZE];
extern unsigned volatile int iot_rx_ring_wr;
extern unsigned int iot_rx_ring_rd;
extern unsigned volatile int iot_tx_ring_wr;
extern unsigned volatile int iot_tx_ring_rd;
extern unsigned char menu_toggle;
volatile unsigned char current_character;
volatile unsigned char character_time_out;
char ok_to_transmit_to_pc;
char getmacadd[] = {"AT+S.GCFG=nv_wifi_macaddr"};
char setBAUD9600[30] = {"AT+S.SCFG=console1_speed,9600"};
char flashmem[5] = {"AT&W"};
char resetBoard[10] = {"AT+CFUN=1"}; 
char setSSID[18] = {"AT+S.SSIDTXT=ncsu"};
char getSSID[13] = {"AT+S.SSIDTXT"};
char setHost[35] = {"AT+S.SCFG=ip_hostname,ECE-306_22_B"};
char getHost[22] = {"AT+S.GCFG=ip_hostname"};
char setNWPriv[27] = {"AT+S.SCFG=wifi_priv_mode,0"};
char getNWPriv[25] = {"AT+S.GCFG=wifi_priv_mode"};
char setNWMode[22] = {"AT+S.SCFG=wifi_mode,1"};
char getNWMode[20] = {"AT+S.GCFG=wifi_mode"};
char checkStatus[9] = {"AT+S.STS"};
char beaconLoss[] = {"AT+S.SCFG=wifi_beacon_loss_thresh,6000"};
char idleTimeout[] = {"AT+S.SCFG=wifi_ap_idle_timeout,600"};

//------------------------------------------------------------------------------
// Functions

void menu(void){
  if(menu_toggle)
    return;
  // Menu Program
  //------------------------------------------------------------------------------
  grab_a_character();
  if (current_character != 0x00){
    if (current_character == 0x2E){
      outchar(current_character);
      if (wait_for_character()){
        print_CR();
        return;
      }
      menu_program();
    }
  }
  //------------------------------------------------------------------------------
}

void grab_a_character(void){
  //------------------------------------------------------------------------------
  if (usb_rx_ring_rd == usb_rx_ring_wr){    // If no character is avalable Return 0x00
    current_character = NO_CHARACTER;
  }else{
    UCA0IE &= ~UCRXIE;                      // Disable USART0 RX interrupt
    current_character = USB_Char_Rx[usb_rx_ring_rd];
    increment_usb_rx_ring();
    UCA0IE |= UCRXIE;                       // Enable USART0 RX interrupt
  }
  //------------------------------------------------------------------------------
}

int wait_for_character(void){
  //------------------------------------------------------------------------------
  // This function waits for a character to be entered.
  // It will time out after ?? seconds.
  // This requires character_time_out be incremented in a timer.
  // The value of the While loop is usually set to 1 or 2 seconds.
  // In the timer associated, it is a 5msec timer and the code is:
  //  if(character_time_out <= 50){
  //    character_time_out++;
  //  }
  //------------------------------------------------------------------------------
  character_time_out = 0;
  while(character_time_out <= 4){
    if (usb_rx_ring_rd != usb_rx_ring_wr){  // Character has arrived
      UCA0IE &= ~UCRXIE;                    // Disable USART0 RX interrupt
      current_character = USB_Char_Rx[usb_rx_ring_rd];
      increment_usb_rx_ring();
      UCA0IE |= UCRXIE;                     // Enable USART0 RX interrupt
      return 0;
    }
    for (int i = 0x10; i > 0; i--);         // Time for flag to set
  }
  return 1;
  //------------------------------------------------------------------------------
}

void menu_program(void){
  //------------------------------------------------------------------------------
  outchar(current_character);
  outchar(0x20);
  switch (current_character) {
  case '.':  // .
    outchar('I');outchar(0x27);outchar('m');outchar(0x20);outchar('H');outchar('e');outchar('r');outchar('e');
    transmit_2_pc_ok = 1;
    break;
    
  case 'B':
  case 'b':
    get_command(setBAUD9600);
    break;
    
  case 'R':
  case 'r':
    reset_command(resetBoard);
    break;
    
  case 'S':
    get_command(setSSID);
    break;
  case 's':
    get_command(getSSID);
    break;
    
  case 'H':
    get_command(setHost);
    break;
  case 'h':
    get_command(getHost);
    break;
    
  case 'P':
    get_command(setNWPriv);
    break;
  case 'p':
    get_command(getNWPriv);
    break;
    
  case 'N':
    get_command(setNWMode);
    break;
  case 'n':
    get_command(getNWMode);
    break;
    
  case 'C':
  case 'c':
    get_command(checkStatus);
    break;
    
  case 'F':
  case 'f':
    get_command(flashmem);
    break;
    
  case 'I':
    get_command(idleTimeout);
    break;
  case 'i':
    get_command(beaconLoss);
    break;
    
  case 'M':  // M
  case 'm':  // m
    get_mac();
    break;
    
  } // end of character determination Switch
  current_character = 0x00;
  print_CR();
  //------------------------------------------------------------------------------
}

void print_CR(void){
  //------------------------------------------------------------------------------
  // This is a print statement prints a carriage return and line feed.
  outchar(0x0D);
  outchar(0x0A);
  //------------------------------------------------------------------------------
}

void outchar(char character){
  //------------------------------------------------------------------------------
  while (!(UCA0IFG & UCTXIFG));           // USCI_A0 TX buffer ready?
  UCA0TXBUF = character;
  //------------------------------------------------------------------------------
}

void increment_iot_rx_ring(void){
  //------------------------------------------------------------------------------
  iot_rx_ring_rd++;
  if (iot_rx_ring_rd >= (SMALL_RING_SIZE)){
    iot_rx_ring_rd = 0;
  }
  //------------------------------------------------------------------------------
}

void increment_usb_rx_ring(void){
  //------------------------------------------------------------------------------
  usb_rx_ring_rd++;
  if (usb_rx_ring_rd >= (SMALL_RING_SIZE)){
    usb_rx_ring_rd = 0;
  }
  //------------------------------------------------------------------------------
}



// ====================================
// IOT
void get_mac(void){                         
  int i;
  for(i=0;i<(sizeof(getmacadd)-1);i++){
    outchar(getmacadd[i]);
    out_wifi(getmacadd[i]);
  }
  out_wifi(0x0D);
  print_CR();
}

void get_command(char* input_String){//allows user to input any command in Termite text box
  //rather than creating several different functions
  int i;
  for(i=0;i<(strlen(input_String));i++){
    outchar(input_String[i]);
    out_wifi(input_String[i]);
  }
  out_wifi(0x0D);
  print_CR();
}

void reset_command(char* input_String){//allows user to input any command in Termite text box
  //rather than creating several different functions
  int i;
  for(i=0;i<(strlen(input_String));i++){
    outchar(input_String[i]);
    out_wifi(input_String[i]);
  }
  out_wifi(0x0D);
  print_CR();
  __delay_cycles(8000000);
  PJOUT &= ~IOT_RESET;
  __delay_cycles(8000000);
  PJOUT |= IOT_RESET;  
}

void out_wifi(char character){
  //------------------------------------------------------------------------------
  while (!(UCA1IFG & UCTXIFG));             // USCI_A1 TX buffer ready?
  UCA1TXBUF = character;
  //------------------------------------------------------------------------------
}

