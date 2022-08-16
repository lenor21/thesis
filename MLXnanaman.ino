#include <DanyBotLCD.h>
#include <ESP8266WiFi.h> 
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
//#include <SPI.h>
#include <Adafruit_MLX90614.h>

WiFiClient wifiClient;
DanyBotLCD lcd(0x23, 16, 2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float duration, distance;
const char *ssid = "HomeWifi";  //ENTER YOUR WIFI SETTINGS 
const char *password = "apungmiling";

//Web/Server address to read/write from 
const char *host = "192.168.1.50";   //IP address of server
const int trigPin = 12;
const int echoPin = 14; 

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin();
  delay(100);

  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting to ");
  Serial.print(ssid);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected");
  Serial.print("NodeMCU IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;

  Serial.print("distance: ");
  Serial.println(distance);
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  Serial.print("*C\tObject = "); 
  Serial.println(mlx.readObjectTempC());

  if(WiFi.status() != WL_CONNECTED){
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    Serial.print("Reconnecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    Serial.println("");
    Serial.println("Connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  
  }

  showTemp();
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
   if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    int temperature = mlx.readObjectTempC();
      HTTPClient http;  
    String MQ7Post,postData;
     MQ7Post = String(temperature);
     postData = "temps=" + MQ7Post ;
  
  http.begin(wifiClient,"http://192.168.1.50/thermometer/add.php");               //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");                  //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
  //-------------------------------------------
  
  //Serial.println("LDR Value=" + ldrvalue);
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  Serial.println("temps= " + MQ7Post );
  
  http.end();  //Close connection

  delay(4000); 
  
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(1000);    //Send a request every 30 seconds
}
