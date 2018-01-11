//------------------------------------------------------------------------------
// File Name : macros.h
// Description: This file contains the macros used by all the other files
//
// Author: Benjamin Tang  
// Date: Nov 2016
// Built with IAR Embedded Workbench Version: 6.50.1
//------------------------------------------------------------------------------


//MACROS========================================================================

//General
#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define IOT_WAKEUP           (0x01) // LED 1
#define IOT_FACTORY          (0x02) // LED 2
#define IOT_STA_MINIAP       (0x04) // LED 3
#define IOT_RESET            (0x08) // LED 4
#define LED5                 (0x10) // LED 5
#define LED6                 (0x20) // LED 6
#define LED7                 (0x40) // LED 7
#define LED8                 (0x80) // LED 8
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CNTL_STATE_INDEX        (3)
#define FALSE                   (0)
#define TRUE                    (1)

// LCD
#define LCD_HOME_L1	     (0x80)
#define LCD_HOME_L2          (0xA0)
#define LCD_HOME_L3          (0xC0)
#define LCD_HOME_L4          (0xE0)
#define CLEAR_REGISTER       (0x0000)
#define FLLN_BITS            (0x03ffu)
#define FLLN_255             (0x00ffu)
#define CSLOCK               (0x01) // Any incorrect password locks registers

#define IO_RESET            (0x00)// (Reset) Set as I/0 

// Port_1
#define V_DETECT_R           (0x01) // Voltage from Right Detector 
#define V_DETECT_L           (0x02) // Voltage from Right Detector 
#define LCD_BACKLITE         (0x04) // Control Signal for LCD_BACKLITE 
#define V_THUMB              (0x08) // Voltage from Thumb Wheel 
#define SPI_CS_LCD           (0x10) // LCD Chip Select 
#define RESET_LCD            (0x20) // LCD Reset 
#define SIMO_B               (0x40) // SPI mode - slave in/master out of USCI_B0 
#define SOMI_B               (0x80) // SPI mode - slave out/master in of USCI_B0 

// Port_2
#define USB_TXD              (0x01) // 
#define USB_RXD              (0x02) // 
#define SPI_SCK              (0x04) //
#define PORT2_PIN3           (0x08) //
#define PORT2_PIN4           (0x10) //
#define CPU_TXD              (0x20) //
#define CPU_RXD              (0x40) //
#define UNKNOWNP2PIN7            (0x80) //

// Port_3
#define X_2                   (0x01) // 
#define Y_2                   (0x02) // 
#define Z_2                   (0x04) //
#define IR_LED               (0x08) //
#define R_FORWARD            (0x10) //
#define L_FORWARD            (0x20) //
#define R_REVERSE            (0x40) //
#define L_REVERSE            (0x80) //

// Port J Pins 
#define LED1                 (0x01) // LED 5 
#define LED2                 (0x02) // LED 6 
#define LED3                 (0x04) // LED 7 
#define LED4                 (0x08) // LED 8 
#define XINR                 (0x10) // XINR 
#define XOUTR                (0x20) // XOUTR 

//init
#define CHAR_SIZE_11         (11)
#define CHAR_SIZE_0          (0)

//Counts
#define RESET               (0)
#define COUNTZERO               (0)
#define COUNTERONE                (1)
#define COUNTERTWO                (2)
#define COUNTTHREE              (3)
#define COUNTFOUR               (4)
#define COUNTFIVE               (5)
#define COUNTSIX                (6)
#define COUNTSEVEN              (7)
#define COUNTEIGHT              (8)
#define COUNTNINE               (9)
#define COUNTTEN                (10)
#define COUNTFOURTEEN           (14)
#define COUNTFORTY              (40)

// Interrupts
#define TA0CCR0_INTERVAL         (1250)
#define TA0CCR1_INTERVAL         (1250)
#define TA0CCR2_INTERVAL         (2500)

// ADC
#define RESET_STATE              (0)
#define char_offset              (48)
#define HEX00                    (0x00) // Case 12 Sub Cases
#define HEX01                    (0x01) // Case 12 Sub Cases
#define HEX02                    (0x02) // Case 12 Sub Cases
#define HEX30                    (0x30) // Case 12 Sub Cases

//PWM
#define OFF                     (0)
#define WHEEL_PERIOD            (8000)

//Serial Communication
#define HEX00                   (0x00)
#define HEX01                   (0x01)
#define HEX08                   (0x08)
#define BEGINNING               (0)
#define SMALL_RING_SIZE         (16)
#define LARGE_RING_SIZE         (16)
#define BRW_9600                (52)
#define MCTLW_9600              (0x4911)
#define BRW_115200              (4)
#define MCTLW_115200            (0x5551)
#define HEXN                    (0x4e)
#define HEXC                    (0x43)
#define HEXS                    (0x53)
#define HEXU                    (0x55)
#define HEXSPACE                (0x20)
#define HEXPOUND                (0x23)
#define HEXONE                  (0x31)
#define RESET                   (0)

//Black Line Follow
#define BLK_LINE_UPPER_THRESHOLD (150)
#define BLK_LINE_LOWER_THRESHOLD (-150)
#define MIN_MOVE_REQ             (400)
#define MANUAL_OFFSET            (10)
#define REAL_SLOW                (1000)
#define SLOW                     (1500)
#define SLOW_MED                 (2000)
#define MED                      (3000)
#define MED_FAST                 (4000)
#define FAST                     (5000)
#define DELAY_PERIOD             (10000)
#define PREEMPTIVE_LINE_VAL     (300)
#define FIRST_FLAG              (1)
#define FUTURE_FLAGGER          (2)
#define AVG_DIVISOR             (2)
#define INTERCEPT_STOP          (200)
#define INTERCEPT_REV           (100)
#define INTERCEPT_STOP2         (330)
#define INTERCEPT_PIVOT         (240)

//HEX_2_BCD
#define FIRST_CHAR_VAL          (0)
#define SECOND_CHAR_VAL         (1)
#define THIRD_CHAR_VAL          (2)
#define FOURTH_CHAR_VAL         (3)
#define FIFTH_CHAR_VAL          (4)
#define HEX_VAL_LOWER_THRESH    (1000)   
#define HEX_MASK                (0x30)
#define HEX_VAL_COUNT_LIMIT     (99)
#define HEX_VAL_COUNT_LIMIT2    (9)
#define HEX_VAL_SUBTRACT        (100)
#define HEX_VAL_SUBTRACT_SML    (10)
#define VALUE_INCREMENTER       (1)

//ADC Process
#define LCD_REFRESH_RATE        (3)
#define CHAR_ARRAY_SIZE         (5)