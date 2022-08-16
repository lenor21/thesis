#include <SoftwareSerial.h>

SoftwareSerial myGSM(8, 7);

char inchar;
int LED = 5;

void setup() {
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    myGSM.begin(19200);
    Serial.begin(19200);
    delay(500);
    myGSM.println("AT+CMGF=1");
    delay(100);
    myGSM.println("AT+CNMI=2,2,0,0,0");
    Serial.println("Waiting for command");

}

void loop() {
  if (myGSM.available()>0) {
    inchar = myGSM.read();
    if ((inchar == 'o') || (inchar == 'O')) {
      delay(50);
      inchar = myGSM.read();
       if ((inchar == 'n') || (inchar == 'N')) {
        digitalWrite(LED, HIGH);
        Serial.println("LED is On..");

        delay(100);
        myGSM.println("AT+CMGD=1,4");
        delay(100);
       }

       else if ((inchar == 'f') || (inchar == 'F')) {
        delay(50);

        inchar = myGSM.read();
        if ((inchar == 'f') || (inchar == 'F')) {
          digitalWrite(LED, LOW);
        Serial.println("LED is Off..");

        delay(100);
        myGSM.println("AT+CMGD=1,4");
        delay(100);
        }
       }
    }
  }

}
