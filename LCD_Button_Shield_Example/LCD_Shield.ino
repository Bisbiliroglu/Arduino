
#include <LiquidCrystal.h>
int button_value = 0;
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
  button_value = analogRead(0);
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);

  lcd.setCursor(4, 1);
  lcd.print(button_value);
  lcd.print("   ");
  lcd.setCursor(10, 1);

  if(button_value > 630 && button_value < 640){
    //select
    lcd.print("select ");
  }else if(button_value > 400 && button_value < 410){
    //left
    lcd.print("left   ");
  }else if(button_value > 90 && button_value < 100){
    //up
    lcd.print("up     ");
  }else if(button_value > 250 && button_value < 260){
    //down
    lcd.print("down   ");
  }else if(button_value > -5 && button_value < 5){
    //right
    lcd.print("right  ");
  }else{
    lcd.print("       ");
  }
  

}
