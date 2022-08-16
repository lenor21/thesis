
#define trigPin 10
#define echoPin 13

float duration, distance;

int pump = 7;
int myLed = 6;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pump, OUTPUT);
  pinMode(myLed, OUTPUT);
  pinMode(5, OUTPUT);
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
  
  /*if (distance >= 400 || distance <=2) {
    Serial.println("Out of range");
  }*/
  if (distance <= 20) {
    digitalWrite(myLed, HIGH);
    digitalWrite(5, HIGH);
    Serial.print(distance);
    Serial.println(" cm");
    digitalWrite(pump, HIGH);
    delay(100);
  }
  else if (distance > 20){
    digitalWrite(pump, LOW);
    digitalWrite(myLed, LOW);
    digitalWrite(5, LOW);
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);
  }
}
