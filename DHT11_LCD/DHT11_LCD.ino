
#include <LiquidCrystal.h>
const int dht11_pin = 2;
int dht11_data[40] = {};
int pulse_width = 0;
int hum1 = 0, temp1 = 0, hum2 = 0, temp2 = 0,checksum = 0, checksum_calc, isDec = 0;
//8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal Tdata + 8bit check sum. 
int button_value = 0;
bool lcd_mode = false;

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int bytetoDecimal(int binnary_array[], int start_index, int last_index){
  int result = 0, ctr = 0;
  
  for(int i = last_index - 1 ; i >= start_index; i--){
    result = round(pow(2,ctr)*binnary_array[i]) + result;
    ctr++;
  }
  
  return result;
}
void setup(void) {
  Serial.begin(9600);  
  lcd.begin(16, 2);
  digitalWrite(dht11_pin, HIGH);
}

void loop(void) {
  
  pinMode(dht11_pin, OUTPUT);
  digitalWrite(dht11_pin, LOW);
  delay(20);
  digitalWrite(dht11_pin, HIGH);
  pinMode(dht11_pin, INPUT_PULLUP);
  delayMicroseconds(200);

  for(int i = 0; i<40; i++){
    pulse_width = pulseIn(dht11_pin, HIGH,90);
   if( pulse_width > 22 && pulse_width < 28){
        dht11_data[i] = 0;
   }else if(pulse_width > 68 ){
        dht11_data[i] = 1;
   }
   
   delayMicroseconds(40);
   pulse_width = 0;
  }
   Serial.print("Hum : ");
   for(int i = 0; i<16; i++){
    if(i == 8){
    Serial.print(".");
    }
    
    Serial.print(dht11_data[i]);
    delay(5);
  }
   Serial.print(" Temp : ");
   for(int i = 16; i<32; i++){
    if(i == 24){
    Serial.print(".");
    }
    Serial.print(dht11_data[i]);
        delay(5);
  }
  hum1      = bytetoDecimal(dht11_data, 0 , 8);
  hum2      = bytetoDecimal(dht11_data, 8 , 16);
  temp1     = bytetoDecimal(dht11_data, 16 , 24);
  temp2     = bytetoDecimal(dht11_data, 24 , 32);
  checksum  = bytetoDecimal(dht11_data, 32 , 40);

  checksum_calc = hum1 + hum2 + temp1 + temp2;
   Serial.print(" Checksum : ");
   for(int i = 32; i<40; i++){
    Serial.print(dht11_data[i]);
    delay(5);
   }
   
  Serial.println();
  Serial.print("Hum : ");
  Serial.print(hum1);
  Serial.print(".");
  Serial.print(hum2);
  Serial.print(" Temp : ");
  Serial.print(temp1);
  Serial.print(".");
  Serial.print(temp2);
  Serial.print(" Checksum_calc : ");
  Serial.print(checksum_calc);
  Serial.print(" Checksum : ");
  Serial.print(checksum);
  Serial.println();


  
  button_value = analogRead(0);
  lcd.clear(); 
  if(lcd_mode){
  lcd.setCursor(0, 0);
  lcd.print("Chks: " + String(checksum) + " = " + String(checksum_calc) );
  lcd.setCursor(0, 1);
  lcd.print(String(temp1) + "." + String(temp2) + (char)223 + "C ");
  //(char)223 = degree symbol
  lcd.setCursor(7, 1);
  lcd.print("%" + String(hum1) + "RH");
  lcd.setCursor(15, 1);
  if((int)checksum == (int)checksum_calc){
      lcd.print(' ');
  }else{
      lcd.print('!');
  }
  }else{
  lcd.setCursor(0, 1);
  lcd.print(" SICAKLIK  NEM" );
  lcd.setCursor(2, 0);
  lcd.print(String(temp1) + "." + String(temp2) + (char)223 + "C ");
  //(char)223 = degree symbol
  lcd.setCursor(10, 0);
  lcd.print("%" + String(hum1) + "RH");
  lcd.setCursor(15, 1);
  if((int)checksum == (int)checksum_calc){
      lcd.print(' ');
  }else{
      lcd.print('!');
  }
  }
 

  if(button_value > 630 && button_value < 640){
    lcd_mode =! lcd_mode;
    //select
  }else if(button_value > 400 && button_value < 410){
    //lef15
  }else if(button_value > 90 && button_value < 100){
    //up
  }else if(button_value > 250 && button_value < 260){
    //down
  }else if(button_value > -5 && button_value < 5){
    //right
  }else{
  }
  
  hum1 = hum2 = temp1 = temp2 = checksum = checksum_calc = 0;
  pinMode(dht11_pin, OUTPUT);
  delay(100);
}
