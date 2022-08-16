
#include <SoftwareSerial.h>
#include <DanyBotLCD.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define trigPin 10
#define echoPin 13

SoftwareSerial myGSM(3, 2);

DanyBotLCD lcd(0x27, 16, 2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float duration, distance, temperature, temp;
float sum;
int i = 0;
String number = "+639982528852";

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
  while (i < 30) {
    temp= mlx.readObjectTempC();
    sum += temp;
    i++;
    delay(1);
  }
  temperature = sum/30.0;
  sum = 0;
  i = 0;
  Serial.println(temperature);
  delay(50);
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
  int myTemp = temperature;
  if (distance = 3) {
    lcd.setCursor(0, 1);
    lcd.print(myTemp);
    //sendMessage();
    delay(5000);
  }
  else if (distance >= 2) {
    //lcd.setCursor(0, 1);
    lcd.clear();
    delay(200);
  }

  if (temperature > 37) {
    sendMessage();
    digitalWrite(7, HIGH);
    delay(200);
    digitalWrite(7, LOW);
    delay(200);
  }

  else if (temperature <= 37) {
    digitalWrite(6, HIGH);
    delay(200);
    digitalWrite(6, LOW);
    delay(200);
  }
  if (temperature > 37) {
    sendMessage();
    digitalWrite(7, HIGH);
    delay(200);
    digitalWrite(7, LOW);
    delay(200);
  }

  else if (temperature <= 37) {
    digitalWrite(6, HIGH);
    delay(200);
    digitalWrite(6, LOW);
    delay(200);
  }
}

void sendMessage() {
  int myMessage = temperature;
  myGSM.println("AT+CMGF=1");
  delay(100);
  myGSM.println("AT+CMGS=\"" + number + "\"\r");
  delay(100);
  myGSM.println("ALERT!!!\n");
  myGSM.println(myMessage);
  delay(100);
  myGSM.println((char)26);
  delay(100);
  Serial.println("SEND");
}
