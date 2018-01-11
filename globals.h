// Global Variables

// main.c
extern volatile unsigned char control_state[CNTL_STATE_INDEX];
extern volatile unsigned int Time_Sequence;
extern char led_smclk;
extern volatile char one_time;
extern volatile unsigned int five_msec_count;
extern char display_line_1[CHAR_SIZE_11];
extern char display_line_2[CHAR_SIZE_11];
extern char display_line_3[CHAR_SIZE_11];
extern char display_line_4[CHAR_SIZE_11];
extern char *display_1;
extern char *display_2;
extern char *display_3;
extern char *display_4;
extern char posL1;
extern char posL2;
extern char posL3;
extern char posL4;
extern char size_count;
extern char big;
extern unsigned int baudrate;

// interrupts


//ADC
extern volatile unsigned int four_counter;
extern volatile unsigned int updateDisplay_Ok;
//extern char displayRight[4];
//extern char displayView[4];

// PWM
extern unsigned int right_reverse_rate;
extern unsigned int left_reverse_rate;
extern unsigned int right_forward_rate;
extern unsigned int left_forward_rate;

//hex_bcd
extern char adc_char[COUNTFOUR];
extern char displayCharRight[COUNTFIVE];
extern char displayCharLeft[COUNTFIVE];
extern char displayCharThumb[COUNTFIVE];

extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
extern volatile unsigned int ADC_Thumb;

// Serial
extern unsigned int temp;
extern volatile unsigned  char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile unsigned char USB_Char_Tx[SMALL_RING_SIZE];

extern volatile char IOT_Char_Rx[SMALL_RING_SIZE];
extern volatile char IOT_Char_Tx[SMALL_RING_SIZE];

extern volatile unsigned int usb_rx_ring_wr;
extern unsigned int usb_rx_ring_rd;
extern volatile unsigned int usb_tx_ring_wr;
extern volatile unsigned int usb_tx_ring_rd;

extern volatile unsigned int iot_rx_ring_wr;
extern volatile unsigned int iot_rx_ring_rd;
extern volatile unsigned int iot_tx_ring_wr;
extern volatile unsigned int iot_tx_ring_rd;

extern unsigned int oneSecCount;
extern int valueFromTeam;
extern char *pointerValueFromTeam;
extern int valueToTeam;
extern int *pointerValueToTeam;
extern int valueRecievedToDisplay[COUNTTHREE];
extern char hexSignal[COUNTEIGHT];

// Clean Up Externs
// adc
extern volatile unsigned int four_counter;
extern volatile unsigned int updateDisplay_Ok;

// hex_bcd
//extern volatile int channelToSwitchCount;

// switch

extern char start_moving;
extern unsigned int moving;
extern int next_shape;
