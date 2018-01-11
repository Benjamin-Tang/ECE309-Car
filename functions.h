//------------------------------------------------------------------------------
// File Name : functions.h
// Description: This file contains the list of declaration of all functions
//
// Author: Benjamin Tang  
// Date: Nov 2016
// Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------


// Function prototypes main
void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);
void Init_LEDs(void);
void Display_Process(void);
void five_msec_sleep(unsigned int fivemsec);

// Function prototypes clocks
void Init_Clocks(void);

// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
__interrupt void TIMER2_B1_ISR(void);
void Init_Timer_A0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);
void measure_delay(void);
void usleep10(unsigned int usec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);

// LCD
void Init_LCD(void);
void WriteIns(char instruction);
void WriteData(char data);
void ClrDisplay(void);
void SetPostion(char pos);
void DisplayOnOff(char data);
void lcd_BIG_mid(void);
void lcd_4line(void);
void lcd_out(char *s, char line, char position);

void grab_a_character(void);
int wait_for_character(void);
void menu(void);

// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);

// Motor Functions
void forward(void);
void reverse(void);
void stop(void);
void sharp_left_turn(void);
void short_forward(void);
void short_reverse(void);

void left_forward_on(void);
void left_forward_off(void);
void right_forward_on(void);
void right_forward_off(void);

void left_reverse_on(void);
void left_reverse_off(void);
void right_reverse_on(void);
void right_reverse_off(void);

// Time Sequences
void wait10(unsigned int usec);

// Shape Paths
void circle_path(void);
void triangle_path(void);
void eight_path(void);
void projFour(void);
void clockwise(void);
void counterClockwise(void);

// ADC
void Init_ADC(void);
void displayRight(unsigned int input);
void PerformConversion(void);
void ADC_Process(void);
void HEXtoBCD(int hex_value);
void HEXtoBCD_Right(int hex_value);
void HEXtoBCD_Left(int hex_value);
void HEXtoBCD_Thumb(int hex_value);
__interrupt void ADC10_ISR(void);

void intercept(void);

// Serial Communication
void out_character(char character);
void Init_Serial_UCA0(int calcNumber, int calcHex);
void Init_Serial_UCA1(int calcNumber, int calcHex);

// Serial Communication to Team
void receiveFromTeam(void);
void startSendToTeam(void);

// Wait for One Second
void waitForSeconds(int second);

//Command_Menu
void implement_command(void);
void grab_com_character(void);
int wait_com_character(void);
void com_menu_program(void);
void print_com_CR(void);
void outchar_com(char);