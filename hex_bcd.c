#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

char adc_char[CHAR_ARRAY_SIZE];
char adc_char_L[CHAR_ARRAY_SIZE];
char adc_char_R[CHAR_ARRAY_SIZE];

//------------------------------------------------------------------------------
//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//------------------------------------------------------------------------------
void HEXtoBCD_Thumb(int hex_value){
int value;
adc_char[FIRST_CHAR_VAL] = '0';
if (hex_value > HEX_VAL_LOWER_THRESH){
hex_value = hex_value - HEX_VAL_LOWER_THRESH;
adc_char[FIRST_CHAR_VAL] = '1';
}
value = RESET;
adc_char[SECOND_CHAR_VAL] = HEX_MASK + value;
while (hex_value > HEX_VAL_COUNT_LIMIT){
hex_value = hex_value - HEX_VAL_SUBTRACT;
value = value + VALUE_INCREMENTER;
adc_char[SECOND_CHAR_VAL] = HEX_MASK + value;
}
value = RESET;
adc_char[THIRD_CHAR_VAL] = HEX_MASK + value;
while (hex_value > HEX_VAL_COUNT_LIMIT2){
hex_value = hex_value - HEX_VAL_SUBTRACT_SML;
value = value + VALUE_INCREMENTER;
adc_char[THIRD_CHAR_VAL] = HEX_MASK + value;
}
adc_char[FOURTH_CHAR_VAL] = HEX_MASK + hex_value;
adc_char[FIFTH_CHAR_VAL] = RESET;
}
//******************************************************************************
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//------------------------------------------------------------------------------
void HEXtoBCD_L_Det_Uncalibrated(int hex_value){
int value;
adc_char_L[FIRST_CHAR_VAL] = '0';
if (hex_value > HEX_VAL_LOWER_THRESH){
hex_value = hex_value - HEX_VAL_LOWER_THRESH;
adc_char_L[FIRST_CHAR_VAL] = '1';
}
value = 0;
adc_char_L[SECOND_CHAR_VAL] = HEX_MASK + value;
while (hex_value > HEX_VAL_COUNT_LIMIT){
hex_value = hex_value - HEX_VAL_SUBTRACT;
value = value + VALUE_INCREMENTER;
adc_char_L[SECOND_CHAR_VAL] = HEX_MASK + value;
}
value = RESET;
adc_char_L[THIRD_CHAR_VAL] = HEX_MASK + value;
while (hex_value > HEX_VAL_COUNT_LIMIT2){
hex_value = hex_value - HEX_VAL_SUBTRACT_SML;
value = value + VALUE_INCREMENTER;
adc_char_L[THIRD_CHAR_VAL] = HEX_MASK + value;
}
adc_char_L[FOURTH_CHAR_VAL] = HEX_MASK + hex_value;
adc_char_L[FIFTH_CHAR_VAL] = RESET;
}
//******************************************************************************
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//******************************************************************************
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//------------------------------------------------------------------------------
void HEXtoBCD_R_Det_Uncalibrated(int hex_value){
int value;
adc_char_R[FIRST_CHAR_VAL] = '0';
if (hex_value > HEX_VAL_LOWER_THRESH){
hex_value = hex_value - HEX_VAL_LOWER_THRESH;
adc_char_R[FIRST_CHAR_VAL] = '1';
}
value = RESET;
adc_char_R[SECOND_CHAR_VAL] = HEX_MASK + value;
while (hex_value > HEX_VAL_COUNT_LIMIT ){
hex_value = hex_value - HEX_VAL_SUBTRACT;
value = value + VALUE_INCREMENTER;
adc_char_R[SECOND_CHAR_VAL] = HEX_MASK + value;
}
value = RESET;
adc_char_R[THIRD_CHAR_VAL] = HEX_MASK + value;
while (hex_value > HEX_VAL_COUNT_LIMIT2){
hex_value = hex_value - HEX_VAL_SUBTRACT_SML;
value = value + VALUE_INCREMENTER;
adc_char_R[THIRD_CHAR_VAL] = HEX_MASK + value;
}
adc_char_R[FOURTH_CHAR_VAL] = HEX_MASK + hex_value;
adc_char_R[FIFTH_CHAR_VAL] = RESET;
}
//******************************************************************************
//------------------------------------------------------------------------------