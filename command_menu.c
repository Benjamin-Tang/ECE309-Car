#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"

#define NO_CHARACTER         (0x00)   // No character available

void left_forward(int);
void right_forward(int);
void left_reverse(int);
void right_reverse(int);
void left_stop(void);
void right_stop(void);
void increment_iot_rx_ring(void);
volatile unsigned char current_com_character;
volatile unsigned char com_character_time_out;
extern volatile unsigned int usb_rx_ring_wr;
extern unsigned int usb_rx_ring_rd;
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Tx[SMALL_RING_SIZE];
extern unsigned volatile int iot_rx_ring_wr;
extern unsigned int iot_rx_ring_rd;
extern unsigned volatile int iot_tx_ring_wr;
extern unsigned volatile int iot_tx_ring_rd;
extern unsigned char menu_toggle;
extern volatile unsigned int usb_rx_ring_wr;
extern volatile char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern volatile unsigned int iot_rx_ring_wr;
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
extern unsigned int line_int_toggle;
int time;
void print_CR(void);
void outchar(char character);
extern volatile char transmit_2_pc_ok;
extern unsigned int follow_toggle;
void Line_Follow (void);

void command_menu(void){
  if(!(menu_toggle))
    return;
  // Menu Program
  //------------------------------------------------------------------------------
  grab_com_character();
  if (current_com_character != 0x00){
    if (current_com_character == '6'){
      outchar_com(current_com_character);
      if (wait_com_character()){
        print_com_CR();
        return;
      }
      com_menu_program();
    }
  }
  //------------------------------------------------------------------------------
}

void grab_com_character(void){
  //------------------------------------------------------------------------------
  if (iot_rx_ring_rd == iot_rx_ring_wr){    // If no character is avalable Return 0x00
    current_com_character = NO_CHARACTER;
  }else{
    UCA1IE &= ~UCRXIE;                      // Disable USART0 RX interrupt
    current_com_character = IOT_Char_Rx[iot_rx_ring_rd];
    increment_iot_rx_ring();
    UCA1IE |= UCRXIE;                       // Enable USART0 RX interrupt
  }
  //------------------------------------------------------------------------------
}

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
int wait_com_character(void){
  com_character_time_out = 0;
  while(com_character_time_out <= 4){
    if (iot_rx_ring_rd != iot_rx_ring_wr){  // Character has arrived
      UCA1IE &= ~UCRXIE;                    // Disable USART0 RX interrupt
      current_com_character = IOT_Char_Rx[iot_rx_ring_rd];
      increment_iot_rx_ring();
      UCA1IE |= UCRXIE;                     // Enable USART0 RX interrupt
      return 0;
    }
    for (int i = 0x10; i > 0; i--);         // Time for flag to set
  }
  return 1;
}

void com_menu_program(void){
  outchar_com(current_com_character);
  outchar_com('6');
  if(current_com_character == '2')
    if(current_com_character == '3')
      if(current_com_character == '7')
  switch (current_com_character) {
  case 'W':
  case 'w':
    display_2 = "Forward";
    posL2 = RESET;
    Display_Process();
    left_forward(3500);
    right_forward(3000);
    __delay_cycles(8000000);
    left_forward(RESET);
    right_forward(RESET);
    display_2 = "";
    posL4 = RESET;
    Display_Process();
    break;
    
  case 'X':
  case 'x':
    display_2 = "Reverse";
    posL2 = RESET;
    Display_Process();
    left_reverse(3000);
    right_reverse(3000);
    __delay_cycles(2500000);
    left_reverse(0);
    right_reverse(0);
    display_2 = "";
    posL4 = RESET;
    break;
    
  case 'D':
  case 'd':
    display_2 = "Left";
    posL2 = RESET;
    Display_Process();
    left_forward(3000);
    right_reverse(3000);
    __delay_cycles(2500000);
    left_forward(0);
    right_reverse(0);                
    display_2 = "";
    posL4 = RESET;
    break;
    
  case 'A':
  case 'a':
    display_2 = "Left";
    posL2 = RESET;
    Display_Process();
    right_forward(3000);
    left_reverse(3000);
    __delay_cycles(2500000);
    right_forward(0);
    left_reverse(0);                //waitForSeconds(6);
    display_2 = "";
    posL4 = RESET;
    break;
    
  case 'S':
    display_2 = "Right";
    posL2 = RESET;
    Display_Process();
    right_reverse(3000);
    left_forward(3000);
    __delay_cycles(2500000);
    right_reverse(0);
    left_forward(0);                //waitForSeconds(6);
    display_2 = "";
    posL4 = RESET;
    
    display_2 = "Right";
    posL2 = RESET;
    Display_Process();
    right_reverse(3000);
    left_forward(3000);
    __delay_cycles(2500000);
    right_forward(0);
    left_reverse(0);                //waitForSeconds(6);
    display_2 = "";
    posL4 = RESET;
    break;
    
  case 's':
    display_2 = "Left";
    posL2 = RESET;
    Display_Process();
    right_forward(3000);
    left_reverse(3000);
    __delay_cycles(2500000);
    right_forward(0);
    left_reverse(0);                //waitForSeconds(6);
    display_2 = "";
    posL4 = RESET;
    
    display_2 = "Right";
    posL2 = RESET;
    Display_Process();
    right_reverse(3000);
    left_forward(3000);
    __delay_cycles(2500000);
    right_reverse(0);
    left_forward(0);                //waitForSeconds(6);
    display_2 = "";
    posL4 = RESET;
    break;
    
    
  case 'F':  
    follow_toggle = 1;
    line_int_toggle = 1;
    Line_Follow();
    break;
  case 'f':
    follow_toggle = 0;
    Line_Follow();
    right_stop();
    left_stop();
    break;
    
  default: 
    left_forward(0);
    right_reverse(0);
    left_reverse(0);
    right_forward(0);
  }

  waitForSeconds(1);
  current_com_character = 0x00;
  print_com_CR();
  //------------------------------------------------------------------------------
}

void print_com_CR(void){
  //------------------------------------------------------------------------------
  // This is a print statement prints a carriage return and line feed.
  outchar_com(0x0D);
  outchar_com(0x0A);
  //------------------------------------------------------------------------------
}

void outchar_com(char character){
  //------------------------------------------------------------------------------
  while (!(UCA1IFG & UCTXIFG));           // USCI_A0 TX buffer ready?
  UCA1TXBUF = character;
  //------------------------------------------------------------------------------
}