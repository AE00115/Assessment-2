#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "ADC.h"
// Function Prototypes
void init();

int sensor = 2;

int x =  ADC_Read(0);
int main(void){

unsigned char Temperature[4];
unsigned char upp[6];
unsigned char dwn[7];
int counter = 17 ;
int counter2 = 14 ;
float celsius;  

  init();
  //unsigned char buffer[4];
   
  while (1)
  {
    int x =  ADC_Read(0);
    int t =  ADC_Read(sensor);
    t = (t*-500)/1023;

    
    // itoa (t , buffer , 10);
     LCD_String_xy(0,0,"Temperature:");
     itoa (t , Temperature , 10);
	   LCD_String_xy(1,0,Temperature);  
     LCD_String_xy(1,4,"Degree C");
     itoa(counter,upp,10);
     itoa(counter2,dwn,10);
            
  _delay_ms(200);
   
    if(x<60) {  //right
    counter2 = counter2 +2;
    LCD_Clear();
      
  }
    else if( x<200) {  //up
     counter = counter +2;
     LCD_Clear();  
    }  
    else if( x<400) { //down
    counter = counter -2 ;
    LCD_Clear();   
      }

    else if(x<600) { //left
    counter2 = counter2 - 2 ;
    LCD_Clear();
     }
    else if(x<800) { //select
    LCD_Clear();
    LCD_String_xy(0,0,"Lower: ");  
    LCD_String_xy(0,6,dwn);
    LCD_String_xy(1,0,"Upper:");
    LCD_String_xy(1,6,upp);
    _delay_ms(1000);
    LCD_Clear(); 
    } 
    else if(x<1100) { 
    counter = counter;
    counter2 = counter2;
   
     }  
            
      if(counter<t){  //upper
        PORTB = PORTB | (1 <<5); //ON
      }
      /* else if (counter>t){ 
      PORTB = PORTB  &!(1 <<5); //off
       }*/
          
      else if(t<counter2 ){  //lower limit
     
      PORTB = PORTB | (1 << 4); //on
       }
       
        
      else if(t>counter2 ){ 
        PORTB = PORTB  &!(1 <<4); //off
      
            
    }
//_delay_ms(400);
 // return 0; 
}

}
void init()
{
  DDRB = DDRB | (1 << 5); 
  DDRC &= ~(1 << 2);   

  // define ports
  //DDRC &= ~(1 << 0); // make it input
  DDRB = DDRB | (1 << 4); // make it output
      LCD_Init ();
      ADC_Init();
}