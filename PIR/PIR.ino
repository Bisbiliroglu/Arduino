int pit_pin = A0;
int led_pin = 3;
int pir_value = 350;

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);          
  digitalWrite(led_pin,LOW);
}

void loop() {
  int sensorDegeri = analogRead(A0); /* Arduinonun A0 ayagindaki gerilim olculuyor */
  Serial.println(sensorDegeri); /* olculen deger seri haberlesme ile yollaniyor */
  if(sensorDegeri >= pir_value){
      digitalWrite(led_pin, !digitalRead(led_pin));
      delay(2000);
  }/*else {
       digitalWrite(led_pin,LOW);
  }*/
  delay(250); /* daha dogru bir olcum icin biraz bekleme kullanilmalidir */
}
