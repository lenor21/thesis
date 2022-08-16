#include <SoftwareSerial.h>
#include <DanyBotLCD.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define trigPin 10
#define echoPin 13

SoftwareSerial myGSM(3, 2);

DanyBotLCD lcd(0x27, 16, 2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float duration, distance;
String number = "+639357249128";

void setup() {
  lcd.init();
  lcd.backlight();
  myGSM.begin(9600);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin();  
  myGSM.begin(9600);
  delay(100);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;

  Serial.print("Distance = ");
  Serial.println(distance);
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  //lcd.setCursor(0, 1);
  //lcd.print(mlx.readObjectTempC());
  //Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); 
  Serial.print(mlx.readObjectTempC()); 
  Serial.println("*C");
  //Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  //Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  Serial.println();
  showTemp();
  //delay(100);
}

void showTemp() {
  int myTemp = mlx.readObjectTempC();
  if (distance < 3) {
    lcd.setCursor(0, 1);
    lcd.print(myTemp);
    delay(5000);
    if (myTemp > 37) {
      sendMessage();
    }
  }
  else if (distance > 3) {
    //lcd.setCursor(0, 1);
    lcd.clear();
    //delay(200);
  }
}

void sendMessage() {
  int myMessage = mlx.readObjectTempC();
  myGSM.println("AT+CMGF=1");
  delay(100);
  myGSM.println("AT+CMGS=\"" + number + "\"\r");
  delay(100);
  myGSM.println("ALERT!!!\nCCS Building/Room 101:\nDetected student with high temperature");
  //myGSM.println(myMessage);
  delay(100);
  myGSM.println((char)26);
  delay(100);
  Serial.println("SEND");
}
