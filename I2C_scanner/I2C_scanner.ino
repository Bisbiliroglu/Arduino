// Ref- Nick Gammon  http://www.gammon.com.au/forum/?id=10896
// I2C Scanner
//Adding A4 & A5 pin logic levels control and set codes

#include <Wire.h>

void setup() {



  Serial.begin (9600);
  while (!Serial) // Waiting for serial connection
  {
  }
  pinMode(A4, OUTPUT);    
  pinMode(A5, INPUT);   
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);

  if ((digitalRead(A4) == HIGH) && (digitalRead(A5) == HIGH))
  {
    Serial.println ();
    Serial.println ("I2C scanner. Scanning ...");
    byte count = 0;

    Wire.begin();
    for (byte i = 8; i < 120; i++)
    {
      Wire.beginTransmission (i);
      if (Wire.endTransmission () == 0)
      {
        Serial.print ("Found address: ");
        Serial.print (i, DEC);
        Serial.print (" (0x");
        Serial.print (i, HEX);
        Serial.println (")");
        count++;
        delay (1);  // maybe unneeded?
      } // end of good response
    } // end of for loop
    Serial.println ("Done.");
    Serial.print ("Found ");
    Serial.print (count, DEC);
    Serial.println (" device(s).");
  }

  else
  {
    Serial.println("Failed - Lines LOW");
  }
}
void loop() {}
