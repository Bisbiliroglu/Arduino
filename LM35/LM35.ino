#include <LiquidCrystal.h>

const int lm35pin1 = 1, lm35pin2 = 2, buttonpin = 0;
float eski_sicaklik = 0;
int button_value = 0, analog_value = 0;
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7, backlight = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



float float_map(long x, long in_min, long in_max, long out_min, long out_max){
  return (float)((x - in_min) * (out_max - out_min)) / (float)((in_max - in_min) + out_min);
}


float readLM35_1(int lm35pin){
  // default 5V analog referes içöin kullanılabilir.
  float temp_value = float_map(analogRead(lm35pin), 0, 1023, 0, 500 );
  for(int i = 0; i<99; i++){
    temp_value = float_map(analogRead(lm35pin), 0, 1023, 0, 500 ) + temp_value;
    analog_value = analogRead(lm35pin);
  }
  if(eski_sicaklik == 0.00)
    return temp_value/100.00;
  return ((temp_value/100.00) + eski_sicaklik)/2;
}

float readLM35_2(int lm35pin){
  //internal 1V1 analog referans için kullanılabilir. 
  float temp_value = float_map(analogRead(lm35pin), 0, 1023, 0, 110 );
  for(int i = 0; i<99; i++){
    temp_value = float_map(analogRead(lm35pin), 0, 1023, 0, 110 ) + temp_value;
    analog_value = analogRead(lm35pin);
  }
  if(eski_sicaklik == 0.00)
    return temp_value/100.00;
  return ((temp_value/100.00) + eski_sicaklik)/2;
}

void setup() {
  lcd.begin(16, 2);
  analogReference( INTERNAL ); //1V1 Referans verir. 
  pinMode(backlight,OUTPUT);
  digitalWrite(backlight , HIGH);

}

void loop() {
   //lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Beyaz : "+(String)readLM35_2(lm35pin1)+(char)223+"C");
   lcd.setCursor(0,1);
   //lcd.print("Analog  :"+(String)analog_value+"  ");
   lcd.print("Siyah : "+(String)readLM35_2(lm35pin2)+(char)223+"C");
   delay(500);

   /*button_value = analogRead(buttonpin);
   if(button_value > 630 && button_value < 640){
    //select
  }else if(button_value > 400 && button_value < 410){
    //left
  }else if(button_value > 90 && button_value < 100){
    //up
  }else if(button_value > 250 && button_value < 260){
    //down
  }else if(button_value > -5 && button_value < 5){
    //right
  }else{
  }
  */
}
