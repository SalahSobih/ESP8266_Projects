// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLiF3Sfev4"
#define BLYNK_DEVICE_NAME "gesh project"
#define BLYNK_AUTH_TOKEN "0r83WJiYx7gFxmZSOuibZ4W5N5fkdk9G"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Omar s";
char pass[] = "omar123456";

//dht11 sensor
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float humidtity,temperature;

// definations of LDR
#define LIGHT_SENSOR_PIN A0 
float percentage_light,analogValue;
String Current_Time = "";

// definations of Fan
#define L_Motor_Of_Fan 4
#define R_Motor_Of_Fan 5

// defintions of leds
#define led_1 12
#define led_2 13
#define led_3 14
#define led_4 15

bool manual_flag = false ;

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
//functions
// for Fan
void Fan_ON(){
  digitalWrite(L_Motor_Of_Fan,HIGH);
  digitalWrite(R_Motor_Of_Fan,LOW);
  Serial.println("Fan ON");
  }

void Fan_OFF(){
  digitalWrite(L_Motor_Of_Fan,LOW);
  digitalWrite(R_Motor_Of_Fan,LOW);
  Serial.println("Fan OFF");
  }

// for Leds
void open_light(){
  digitalWrite(led_1,HIGH);
  digitalWrite(led_2,HIGH);
  digitalWrite(led_3,HIGH);
  digitalWrite(led_4,HIGH);
  }

void close_light(){
  digitalWrite(led_1,LOW);
  digitalWrite(led_2,LOW);
  digitalWrite(led_3,LOW);
  digitalWrite(led_4,LOW);
  }
  
BLYNK_WRITE(V0)
{
  if(param.asInt()==1){
   manual_flag = true;
  }
  else{
   manual_flag = false;
  }
}

BLYNK_WRITE(V1)
{
  if (manual_flag == true)
  {
  if(param.asInt()==1)
    Fan_ON();
  else
    Fan_OFF();
}
}
BLYNK_WRITE(V2)
{
  if (manual_flag == true)
  {
  if(param.asInt()==1)
    open_light();
  else
    close_light();
}
}

void sendSensor()
{
   
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.virtualWrite(V3, temperature);
  Blynk.virtualWrite(V4, humidtity);
  Blynk.virtualWrite(V5, percentage_light);
  Blynk.virtualWrite(V6, Current_Time);
}

void setup()
{
   // Debug console
   Serial.begin(115200);
   pinMode(L_Motor_Of_Fan,OUTPUT);
   pinMode(R_Motor_Of_Fan,OUTPUT);
   pinMode(led_1,OUTPUT);
   pinMode(led_2,OUTPUT);
   pinMode(led_3,OUTPUT);
   pinMode(led_4,OUTPUT);
   close_light();
   Fan_OFF();
  
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  humidtity = dht.readHumidity();
  temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 /* if (isnan(humidtity) || isnan(temperature)) {
  Serial.println("Failed to read from DHT sensor!");
  return;
  }*/
  if (manual_flag == false){
   if(temperature >= 29.5)
      Fan_ON();
   else 
      Fan_OFF();
 }
  Serial.print("Humidtity = ");
  Serial.print(humidtity);
  Serial.print(" %");
  Serial.print("\t");
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" C");

  analogValue = analogRead(LIGHT_SENSOR_PIN);
  percentage_light = (analogValue/6.5);
  Serial.print("percentage Light = ");
  Serial.print(percentage_light);
  Serial.print(" %");
  
 if (manual_flag == false){
   if (percentage_light < 10.0)
      open_light();
   else  
      close_light(); 
 }
 
 if (percentage_light < 10.0) {
    Current_Time = "مظلم";
    Serial.println(Current_Time);
  } else if (percentage_light < 20.0) {
    Current_Time = "خافت";
    Serial.println(Current_Time);
  } else if (percentage_light < 50.0) {
    Current_Time = "مضئ";
    Serial.println(Current_Time);
  } else if (percentage_light < 90.0) {
    Current_Time = "مضئ جدا";
    Serial.println(Current_Time);
  }
  Blynk.run();
  timer.run();
}
