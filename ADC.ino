#include <avr/io.h>
#include "ADC.h"

void ADC_Init() // enable the ADC from the ADCSRA register by setting ADEN
 {
  //Select ADC prescaler from ADCSRA register
  //BY setting l ADPS2 , ADPS1 , ADPS0 
  // 16000000/128 = 125000
  ADCSRA = ADCSRA | (1 << ADEN);
  ADCSRA = ADCSRA | (1 << ADPS0);
  ADCSRA = ADCSRA | (1 << ADPS1);
  ADCSRA = ADCSRA | (1 << ADPS2);

  ADMUX = ADMUX | (1 << REFS0);
  //Select the reference voltage from the ADMUX register
  // We'll use the arduino refrence do Set REFS0 and Clear REFS1
  ADMUX = ADMUX & ~(1 << REFS1);
}

int ADC_Read(int channel){ 
  //Clear the MUX bits in ADMUX register
  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘ch’ between 0 and 7

  ADMUX = ADMUX & ~(1 << MUX0);
  ADMUX = ADMUX & ~(1 << MUX1);
  ADMUX = ADMUX & ~(1 << MUX2);
  ADMUX = ADMUX & ~(1 << MUX3);
  ADMUX = ADMUX | channel;

  //Start ADC conversion using ADSC bit in ADCSRA register
  //SET BIT 6 
  ADCSRA = ADCSRA | (1 << ADSC);
  
  //Wait for conversion to complete 
  //This can be done using a while loop that checks if the ADSC bit turned to 0

  while(ADCSRA & (1 << ADSC));
   
   // return ADC value

  return ADC;
}