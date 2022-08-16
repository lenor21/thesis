#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);
//#define serialCom 9600

#define trigPin 12
#define echoPin 13

const char* ssid = "HomeWifi";
const char* password = "apungmiling";
const char* host = "192.168.1.50";

float duration, distance;

void setup() {
 Serial.begin(115200);
 mySerial.begin(115200);

 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

 mySerial.println("AT+CWJAP=\"HomeWifi\",\"apungmiling*\"");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(5000);

  mySerial.println("AT+CIPSTART=\"TCP\",\"192.168.1.50\",80");
  mySerial.print("GET /distance/connect.php?distance=");
  mySerial.print(distance);
  mySerial.print(" ");
  mySerial.print("HTTP/1.1\r\n");
  mySerial.print("Host: 192.168.1.50");
  mySerial.println("AT+CIPCLOSE");
  delay(500);
  /*mySerial.println("AT+RST");
  delay(2000);
  mySerial.println("AT+CWMODE=1");
  delay(2000);
  mySerial.println("AT+RST");
  delay(2000);

  mySerial.println("AT+CWJAP=\"HomeWifi\",\"apungmiling*\"");
  delay(1000);

  mySerial.println("AT+CIPSTART=\"TCP\",\"192.168.1.50\",80");
  delay(5000);
  mySerial.println("AT+CIPSEND=123");
  delay(5000);
  //mySerial.print("GET /Intranet/Interface/modules/php/temp/temp.php?sensorid=\"1\"?humidity=\"1\"&temp=" + String(temperature) + " HTTP/1.0\r\n");
  mySerial.print("Host: 192.168.1.50");
  delay(5000);
  mySerial.println("AT+CIPCLOSE");
  delay(5000);

  digitalWrite(9, LOW);
  digitalWrite(7, LOW);*/
}
