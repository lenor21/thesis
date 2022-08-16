#include <SoftwareSerial.h>

SoftwareSerial myGSM(3, 2);
int butswitch = 7;
int butstate;
int count = 0;
String number = "+639357249128";
void setup() {
 pinMode(butswitch, INPUT_PULLUP);
 myGSM.begin(9600);
 Serial.begin(9600);
 delay(100);
}

void loop() {
 butstate = digitalRead(butswitch);

 if (butstate == LOW) {
  Serial.println(butstate);
  sendMessage();
  //callGSM();
 }
}

void sendMessage() {
  myGSM.println("AT+CMGF=1");
  delay(100);
  myGSM.println("AT+CMGS=\"" + number + "\"\r");
  delay(100);
  myGSM.println("HELLO WORLD");
  delay(100);
  myGSM.println((char)26);
  delay(100);
  Serial.println("SEND");
}

void callGSM()
{
  myGSM.print("ATD");
  delay(100);
  myGSM.print("+639357249128");
  delay(100);
  myGSM.println(";");

  delay(20000);

  myGSM.print("ATH");
  delay(100);
} 
