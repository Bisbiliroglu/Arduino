/**
  ******************************************************************************
  * @Developer            : Barış İşbiliroğlu
  * @Date                 : 13.08.2019 
  * @Components            16X2 LCD
  *                        DHT22
  *                        DS1302
  *                        Arduino Nano
  ******************************************************************************
  *@Pinmap
  ******************************************************************************
  *
  *@LCD 
  *RS   D9
  *E    D8 
  *D4   D3
  *D5   D4
  *D6   D6  
  *D7   D7
  *A    D12 
  *
  *@DHT22 
  *DAT  D2
  *
  *@DS1302
  *RST  A2
  *I/O  A1
  *SCK  A0
  ******************************************************************************
  *
  ******************************************************************************
  */

#include <LiquidCrystal.h>
#include <DHT.h>
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include<stdio.h> 

#define lcdDarkHourBeign  22
#define lcdDarkHourEnd    8

LiquidCrystal lcd(9, 8, 3, 4, 6, 7);
DHT dht(2, DHT22);
ThreeWire myWire(A1,A0,A2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
char stringBuffer[16];

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  Serial.begin(115200);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);   
  Rtc.Begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
    lcd.setCursor(0, 1);
    lcd.print("ERROR");
    //Serial.println("DHT ERROR");
 } else {

  lcd.setCursor(0, 0);
  lcd.print(t);
  lcd.setCursor(5, 0);
  lcd.print((char)223);
  lcd.setCursor(6, 0);
  lcd.print("C   %");


  lcd.setCursor(11, 0);
  lcd.print(h);

 /* Serial.print(t);
  Serial.print("C %");
  Serial.println(h);*/
 }

  RtcDateTime now = Rtc.GetDateTime();
  //sprintf(stringBuffer, "%02d:%02d:%02d %02d/%02d/%d",now.Hour(), now.Minute(), now.Second(), now.Day() , now.Month(), now.Year() ); 
  sprintf(stringBuffer, "%02d:%02d %02d/%02d/%d  ",now.Hour(), now.Minute(), now.Day() , now.Month(), now.Year() ); 

  lcd.setCursor(0, 1);
  lcd.print(stringBuffer);
  //Serial.println(stringBuffer);

  if(now.Hour() >= lcdDarkHourBeign || now.Hour() < lcdDarkHourEnd ){
    digitalWrite(12, LOW);   
  }else{
    digitalWrite(12, HIGH);   
  }
  delay(1000);
}
