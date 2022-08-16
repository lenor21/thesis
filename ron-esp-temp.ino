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

float duration, distance, tem;
const int trigPin = 12;
const int echoPin = 14;                   // Initialize the Led_OnBoard 

//----------I assume you have successfully accessed the sensors. And below is the variable. I made it an arbitrary value.

//----------

const char* ssid = "HomeWifi";                  // Your wifi Name       
const char* password = "apungmiling";          // Your wifi Password

const char *host = "192.168.1.50"; //Your pc or server (database) IP, example : 192.168.0.0 , 
//if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.

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

  if (mlx.readObjectTempC() > 37) {
    wifi();
  }
  showTemp();

}

void showTemp() {
  int myTemp = mlx.readObjectTempC();
  if (distance < 3) {
    lcd.setCursor(0, 0);
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    lcd.print(myTemp);
    delay(5000);
  }
  else if (distance > 3) {
    //lcd.setCursor(0, 1);
    lcd.clear();
    //delay(200);
  }
}

void wifi() {
  Serial.println(mlx.readObjectTempC());
  // put your main code here, to run repeatedly:
  tem = mlx.readObjectTempC();
  //int tem = distance;
  HTTPClient http;    //Declare object of class HTTPClient

  //-------------------------------------------to send data to the database
  String MQ7Post, postData;
  MQ7Post = String(tem);   //String to interger conversion
                            //String to interger conversion
  
  postData = "mq7val=" + MQ7Post ;
  
  http.begin(wifiClient,"http://192.168.1.50/nodemcu/InsertDB.php");               //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");                  //Specify content-type header
 
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload
  //-------------------------------------------
  
  //Serial.println("LDR Value=" + ldrvalue);
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  Serial.println("MQ7= " + MQ7Post );
  
  http.end();  //Close connection

  //delay(4000);  //Here there is 4 seconds delay plus 1 second delay below, so Post Data at every 5 seconds
}
