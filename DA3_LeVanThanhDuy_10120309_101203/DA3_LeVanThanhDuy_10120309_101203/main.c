#include <16f877a.h>
#FUSES NOWDT,PUT,HS,NOPROTECT,NOLVP
#device *=16 adc=10
#use delay (clock=20000000) // su dung thach anh 20mhz

#define LCD_ENABLE_PIN  PIN_C0                                    ////
#define LCD_RS_PIN      PIN_C1                                    ////
#define LCD_RW_PIN      PIN_C2  

#define LCD_DATA4       PIN_D4                                    ////
#define LCD_DATA5       PIN_D5                                    ////
#define LCD_DATA6       PIN_D6                                    ////
#define LCD_DATA7       PIN_D7 
#include <lcd.c>

//!#define LCD_ENABLE_PIN  PIN_D2                                    ////
//!#define LCD_RS_PIN      PIN_D0////
//!#define LCD_RW_PIN      PIN_D1  
//!
//!#define LCD_DATA4       PIN_D4                                    ////
//!#define LCD_DATA5       PIN_D5                                    ////
//!#define LCD_DATA6       PIN_D6                                    ////
//!#define LCD_DATA7       PIN_D7 
//!#include <lcd.c>



#define cambien input(pin_B0)

float vl_real;
float do_am;
   
long map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void set_adc_(){
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(ALL_ANALOG);
   set_adc_channel(0);//Doc gia tri adc o chan A0
}

void main(){
    //khoi tao lcd 
   delay_ms(200);
   lcd_init();
    //doc adc
   set_adc_();
//!   
   lcd_gotoxy(1,1);
   printf(lcd_putc,"Do Am:");
   lcd_gotoxy(13,1);
   printf(lcd_putc,"%%");

   delay_ms(200);
   while(1){
      output_bit(pin_B1,1);
      delay_ms(100);
      output_bit(pin_B1,0);
      delay_ms(100);
      
      if(cambien == 1)
         output_bit(pin_B2,1);
      else
         output_bit(pin_B2,0);
      
      delay_us(10);
      vl_real = read_adc();
      
      lcd_gotoxy(8,1);
      do_am = map(vl_real,1023,0,0,100); // gia tri adc doc duoc
      printf(lcd_putc,"%0.1f",do_am);
      
      if(do_am < 40){
         lcd_gotoxy(1,2);
         printf(lcd_putc,"BAT MAY");
         output_bit(pin_c7,1);
      }
      else if(do_am > 55){
         output_bit(pin_c7,0);
         lcd_gotoxy(1,2);
         printf(lcd_putc,"TAT MAY");
      }
   }
}
