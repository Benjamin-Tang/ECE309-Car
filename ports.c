//------------------------------------------------------------------------------
//  File name : ports.c
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Author: Benjamin Tang  
//  Date: Nov 2016
//  Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "macros.h"
#include  "msp430.h"
#include  "functions.h"


void Init_Ports(void){
  //============================================================================
  // Function name: Init_Ports
  //
  // Description: This function calls the rest of the initialization functions.
  // 
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: N/A
  //
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_PortJ();
}

void Init_Port1(void){
  //============================================================================
  // Function name: Init_Port1
  //
  // Description: This function will initialize all pins in port 1.
  // 
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: N/A
  // IO_RESET          (0x00)
  // V_DETECT_R           (0x01) // Voltage from Right Detector 
  // V_DETECT_L           (0x02) // Voltage from Right Detector 
  // LCD_BACKLITE         (0x04) // Control Signal for LCD_BACKLITE 
  // V_THUMB              (0x08) // Voltage from Thumb Wheel 
  // SPI_CS_LCD           (0x10) // LCD Chip Select 
  // RESET_LCD            (0x20) // LCD Reset 
  // SIMO_B               (0x40) // SPI mode - slave in/master out of USCI_B0 
  // SOMI_B               (0x80) // SPI mode - slave out/master in of USCI_B0 
  
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  P1SEL0 = IO_RESET;               // P1 set as I/0 
  P1SEL1 = IO_RESET;               // P1 set as I/0 
  P1DIR = IO_RESET;                // Set P1 direction to input
  P1OUT = IO_RESET;
  
  P1SEL0 |= V_DETECT_R;        // V_DETECT_R selected 
  P1SEL1 |= V_DETECT_R;        // V_DETECT_R selected
  
  P1SEL0 |= V_DETECT_L;        // V_DETECT_L selected 
  P1SEL1 |= V_DETECT_L;        // V_DETECT_L selected
  
  P1SEL0 &= ~LCD_BACKLITE;     // LCD_BACKLITE GPI/O selected 
  P1SEL1 &= ~LCD_BACKLITE;     // LCD_BACKLITE GPI/O selected 
  
  P1OUT &= ~LCD_BACKLITE;       // LCD_BACKLITEPort Pin set low 
  P1DIR |= LCD_BACKLITE;       // Set LCD_BACKLITE direction to output
  
  P1SEL0 |= V_THUMB;           // V_THUMB selected 
  P1SEL1 |= V_THUMB;           // V_THUMB selected
  
  P1SEL0 &= ~SPI_CS_LCD;       // SPI_CS_LCD GPI/O selected 
  P1SEL1 &= ~SPI_CS_LCD;       // SPI_CS_LCD GPI/O selected 
  P1OUT |= SPI_CS_LCD;         // SPI_CS_LCD Port Pin set high 
  P1DIR |= SPI_CS_LCD;         // Set SPI_CS_LCD output direction
  
  P1SEL0 &= ~RESET_LCD;        // RESET_LCD GPI/O selected 
  P1SEL1 &= ~ RESET_LCD;       // RESET_LCD GPI/O selected 
  P1OUT &= ~ RESET_LCD;        // RESET_LCD Port Pin set low 
  P1DIR |= RESET_LCD;          // Set RESET_LCD output direction
  
  P1SEL0 &= ~SIMO_B;           // SIMO_B selected 
  P1SEL1 |= SIMO_B;            // SIMO_B selected 
  P1DIR |= SIMO_B;             // SIMO_B set to Output 
  P1SEL0 &= ~SOMI_B;           // SOMI_B is used on the LCD
  
  P1SEL1 |= SOMI_B;            // SOMI_B is used on the LCD 
  P1OUT |= SOMI_B;             // SOMI_B Port Pin set for Pull-up 
  P1DIR &= ~SOMI_B;            // SOMI_B set to Input 
  P1REN |= SOMI_B;             // Enable pullup resistor 
}

void Init_Port2(void){ 
  //============================================================================
  // Function name: Init_Port2
  //
  // Description: This function will initialize all pins in port 2.
  // 
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: N/A
  
  // IO_RESET            (0x00) //
  // USB_TXD              (0x01) // 
  // USB_RXD              (0x02) // 
  // SPI_SCK              (0x04) //
  // UNKNOWNP23           (0x08) //
  // UNKNOWNP24           (0x10) //
  // CPU_TXD              (0x20) //
  // CPU_RXD              (0x40) //
  // UNKNOWN27            (0x80) //
  
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  P2SEL0 = IO_RESET;               // P2 set as I/0 
  P2SEL1 = IO_RESET;               // P2 set as I/0 
  P2DIR = IO_RESET;                // Set P2 direction to input
  P2OUT = IO_RESET;
  
  P2SEL1 |= USB_TXD;                    //  
  P2SEL0 &= ~USB_TXD;                   // 
  P2OUT |= USB_TXD;                     // 
  P2DIR &= ~USB_TXD;                    //
  
  P2SEL1 |= USB_RXD;                    //  
  P2SEL0 &= ~USB_RXD;                   // 
  P2OUT &= ~USB_RXD;                    // 
  P2DIR &= ~USB_RXD;                    //
  P2REN &= ~USB_RXD;                    // Disable pullup resistor 
  
  P2SEL1 |= SPI_SCK;                    //  
  P2SEL0 &= ~SPI_SCK;                   // 
  P2OUT |= SPI_SCK;                     // 
  P2DIR &= ~SPI_SCK;                    //
  
  P2SEL0 &= ~PORT2_PIN3;              //
  P2SEL1 &= ~PORT2_PIN3;              // 
  P2OUT &= ~PORT2_PIN3;               //
  P2DIR &= ~PORT2_PIN3;               //
  P2REN |= PORT2_PIN3;               // 
  
  P2SEL0 &= ~PORT2_PIN4;         
  P2SEL1 &= ~PORT2_PIN4;          
  P2OUT &= ~PORT2_PIN4;          
  P2DIR &= ~PORT2_PIN4;          
  P2REN |= PORT2_PIN4;           
  
  P2SEL1 |= CPU_TXD;                    //  
  P2SEL0 &= ~CPU_TXD;                   // 
  P2OUT |= CPU_TXD;                     // 
  P2DIR &= ~CPU_TXD;                    //
  
  P2SEL1 |= CPU_RXD;                    //  
  P2SEL0 &= ~CPU_RXD;                   // 
  P2OUT &= ~CPU_RXD;                    // 
  P2DIR &= ~CPU_RXD;                    //
  P2REN |= CPU_RXD;                     // 
  
  P2SEL0 &= ~UNKNOWNP2PIN7;         
  P2SEL1 &= ~UNKNOWNP2PIN7;          
  P2OUT &= ~UNKNOWNP2PIN7;          
  P2DIR &= ~UNKNOWNP2PIN7;          
  P2REN |= UNKNOWNP2PIN7;  
}

void Init_Port3(void){ 
  //============================================================================
  // Function name: Init_Port3
  //
  // Description: This function will initialize all pins in port 3.
  // 
  // Passed : no variables passed
  // Locals: no variables declared
  // Returned: no values returned
  // Globals: N/A
  
  // IO_RESET                  (0x00) //
  // X_2                         (0x01) // 
  // Y_2                         (0x02) // 
  // Z_2                         (0x04) //
  // IR_LED                     (0x08) //
  // R_FORWARD                  (0x10) //
  // L_FORWARD                  (0x20) //
  // R_REVERSE                  (0x40) //
  // L_REVERSE                  (0x80) //
  
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  P3SEL0 = IO_RESET;               // P3 set as I/0 
  P3SEL1 = IO_RESET;               // P3 set as I/0 
  P3DIR = IO_RESET;   
  P3OUT = IO_RESET;
  
  P3SEL0 &= ~X_2;         
  P3SEL1 &= ~X_2;          
  P3OUT &= ~X_2;          
  P3DIR &= ~X_2;          
  P3REN &= ~X_2;  
  
  P3SEL0 &= ~Y_2;         
  P3SEL1 &= ~Y_2;          
  P3OUT &= ~Y_2;          
  P3DIR &= ~Y_2;          
  P3REN &= ~Y_2;  
  
  P3SEL0 &= ~Z_2;         
  P3SEL1 &= ~Z_2;          
  P3OUT &= ~Z_2;          
  P3DIR &= ~Z_2;          
  P3REN &= ~Z_2;  
  
  P3SEL0 &= ~IR_LED;        
  P3SEL1 &= ~IR_LED;       
  P3OUT &= ~IR_LED;         
  P3DIR |= IR_LED; 
       
  P3SEL0 |= R_FORWARD;        
  P3SEL1 &= ~R_FORWARD;       
  P3DIR |= R_FORWARD;  
       
  P3SEL0 |= L_FORWARD;        
  P3SEL1 &= ~L_FORWARD;       
  P3DIR |= L_FORWARD;         
        
  P3SEL0 |= R_REVERSE;        
  P3SEL1 &= ~R_REVERSE;       
  P3DIR |= R_REVERSE;       
       
  P3SEL0 |= L_REVERSE;        
  P3SEL1 &= ~L_REVERSE;       
  P3DIR |= L_REVERSE;      
}

void Init_Port4(void){
  //============================================================================
  // Function name: Init_Port4
  //
  // Configure PORT 4
  // Port 4 has only two pins
  // Port 4 Pins
  // SW1 (0x01) // Switch 1
  // SW2 (0x02) // Switch 2
  
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  
  P4SEL0 = IO_RESET;           // P4 set as I/0
  P4SEL1 = IO_RESET;           // P4 set as I/0
  P4DIR = IO_RESET;            // Set P4 direction to input
  //P4OUT = IO_RESET;
  
  // SW1
  P4SEL0 &= ~SW1;               // SW1 set as I/0
  P4SEL1 &= ~SW1;               // SW1 set as I/0
  P4DIR &= ~SW1;                // Direction = input
  P4OUT |= SW1;                 // Configure pullup resistor
  P4REN |= SW1;                 // Enable pullup resistor
  
  // Interrupts
  P4IES |= SW1;                 // SW1 Hi/Lo edge interrupt
  P4IFG &= ~SW1;                // IFG SW1 cleared
  P4IE |= SW1;                  // SW1 interrupt Enabled
  
  // SW2
  P4SEL0 &= ~SW2;               // SW2 set as I/0
  P4SEL1 &= ~SW2;               // SW2 set as I/0
  P4DIR &= ~SW2;                // Direction = input
  P4OUT |= SW2;                 // Configure pullup resistor
  P4REN |= SW2;                 // Enable pullup resistor
  
  // Interrupts
  P4IES |= SW2;                 // SW2 Hi/Lo edge interrupt
  P4IFG &= ~SW2;                // IFG SW2 cleared
  P4IE |= SW2;                  // SW2 interrupt enabled
  //----------------------------------------------------------------------------
}

void Init_PortJ(void){ 
  //============================================================================
  // Function name: Init_PortJ
  //
  // Description: This function will initialize all pins in port J.
  // 
  // Port J Pins 
  // IOT_WAKEUP                     (0x01) // LED 5 
  // IOT_FACTORY                    (0x02) // LED 6 
  // IOT_STA_MINIAP                 (0x04) // LED 7 
  // IOT_RESET                      (0x08) // LED 8 
  // XINR                 (0x10) // XINR 
  // XOUTR                (0x20) // XOUTR 
  
  //  Benjamin Tang  
  //  Date: Sept 2016
  //  Built with IAR Embedded Workbench Version: 6.50.1
  //============================================================================
  PJSEL0 = IO_RESET;               // PJ set as I/0 
  PJSEL1 = IO_RESET;               // PJ set as I/0 
  PJDIR = IO_RESET;                // Set PJ direction to output 
  PJOUT = IO_RESET;
  
  PJSEL0 &= ~IOT_WAKEUP; 
  PJSEL1 &= ~IOT_WAKEUP; 
  PJOUT &= ~IOT_WAKEUP; 
  PJDIR |= IOT_WAKEUP;               // Set PJ Pin 1 direction to output
  
  PJSEL0 &= ~IOT_FACTORY; 
  PJSEL1 &= ~IOT_FACTORY; 
  PJOUT &= ~IOT_FACTORY; 
  PJDIR |= IOT_FACTORY;               // Set PJ Pin 2 direction to output
  
  PJSEL0 &= ~IOT_STA_MINIAP; 
  PJSEL1 &= ~IOT_STA_MINIAP; 
  PJOUT |= IOT_STA_MINIAP; 
  PJDIR |= IOT_STA_MINIAP;               // Set PJ Pin 3 direction to output
  
  PJSEL0 &= ~IOT_RESET; 
  PJSEL1 &= ~IOT_RESET; 
  PJDIR |= IOT_RESET;               // Set P3 Pin 4 direction to output 
  PJOUT &= ~IOT_RESET;
}


