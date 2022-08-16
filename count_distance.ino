#include <DanyBotLCD.h>

#define trigPin1 10
#define echoPin1 13
#define trigPin2 11
#define echoPin2 12

DanyBotLCD lcd(0x23, 16, 2);

float duration, distance,duration2, distance2;
int count = 0;

int passLed = 7;
int notPassLed = 6;
int plusLed = 5;
int minusLed = 4;
int myBuzzer = 3;


void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(myBuzzer, OUTPUT);
  pinMode(plusLed, OUTPUT);
  pinMode(passLed, OUTPUT);
  pinMode(notPassLed, OUTPUT);
}

void loop() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration = pulseIn(echoPin1, HIGH);
  distance = (duration / 2) * 0.0343;
  //================================Try me nung gagana ya par=============================
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 / 2) * 0.0343;
  

  lcd.setCursor(0, 0);
  lcd.print("Student Count: ");
  Serial.print("Distance = ");
  //lcd.setCursor(0, 1);
  //lcd.print(count);
  

 if (distance <= 20) {
    count++;
    delay(1500);
    digitalWrite(plusLed, HIGH);
    digitalWrite(myBuzzer, HIGH);
    Serial.print(distance);
    Serial.println(" cm");
    
    if(count == 3){
      digitalWrite(myBuzzer, HIGH);
      digitalWrite(plusLed, HIGH);
      delay(500);
      digitalWrite(myBuzzer, LOW);
      digitalWrite(plusLed, LOW);
      delay(500);
      digitalWrite(myBuzzer, HIGH);
      digitalWrite(plusLed, HIGH);
      delay(500);
      digitalWrite(myBuzzer, LOW);
      digitalWrite(plusLed, LOW);
      delay(500);
      digitalWrite(myBuzzer, HIGH);
      digitalWrite(plusLed, HIGH);
      delay(500);
      digitalWrite(myBuzzer, LOW);
      digitalWrite(plusLed, LOW);
      delay(500);
      digitalWrite(myBuzzer, HIGH);
      digitalWrite(plusLed, HIGH);
      delay(500);
      digitalWrite(myBuzzer, LOW);
      digitalWrite(plusLed, LOW);
      delay(500);
      digitalWrite(myBuzzer, HIGH);
      digitalWrite(plusLed, HIGH);
      delay(500);
      digitalWrite(myBuzzer, LOW);
      digitalWrite(plusLed, LOW);
      delay(500);
    }
    else if(count > 3){
      digitalWrite(myBuzzer, LOW);
      digitalWrite(plusLed, LOW);
     
    }
  }
  
  else if (distance > 30){
    digitalWrite(plusLed, LOW);
    digitalWrite(myBuzzer, LOW);
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(500);
    
  
  
  if (distance2 <= 30) {
    count--;
    delay(1500);
    digitalWrite(minusLed, HIGH);
    digitalWrite(myBuzzer, HIGH);
    Serial.print(distance2);
    Serial.println(" cm");
    if (count < 0) {
      digitalWrite(minusLed, LOW);
      digitalWrite(myBuzzer, LOW);
    }
  }
  else if (distance2 > 30){
    digitalWrite(minusLed, LOW);
    digitalWrite(myBuzzer, LOW);
    Serial.print(distance2);
    Serial.println(" cm");
    delay(100);
  }
 
  if (count < 3){
    digitalWrite(passLed, HIGH);
    digitalWrite(notPassLed, LOW);
    delay(200);
  }
  else if(count >= 3){
    digitalWrite(passLed, LOW);
    digitalWrite(notPassLed, HIGH);
    delay(200);
  }

  count = constrain(count, 0, 3);
  lcd.setCursor(0, 1);
  lcd.print(count);
}
