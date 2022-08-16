#include <SoftwareSerial.h>
SoftwareSerial myserial(7,8);

void setup() {
  myserial.begin(9600);
  Serial.begin(9600);
  Serial.println("S-Send sms");

}

void loop() {
  if (Serial.available()>0)
  switch(Serial.read()){
    case 's':
    SendMessage();
    break;
  }
}

void SendMessage (){
  myserial.println("AT+CMGF=1"); 
  delay(1000);
  myserial.println("AT+CNMI=2,2,0,0,0"); 
  delay(1000);
  myserial.println("ATD+639982528852;");
  delay(1000);
  myserial.println("HEY!!!!! Are You Okay?");
  delay(1000);
  myserial.println((char)26);
  delay(1000);
}
