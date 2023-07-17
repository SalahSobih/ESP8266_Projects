#include <DHT.h>
#define DHTPIN 2          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
float humidtity,temperature;

// definations of Fan
#define L_Motor_Of_Fan 4
#define R_Motor_Of_Fan 5

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

void setup() {
 Serial.begin(115200);
 dht.begin();
 pinMode(L_Motor_Of_Fan,OUTPUT);
 pinMode(R_Motor_Of_Fan,OUTPUT);
}

void loop() {
humidtity = dht.readHumidity();
temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

if(temperature >= 27.5)
  Fan_ON();
else 
  Fan_OFF();

Serial.print("Humidtity = ");
Serial.print(humidtity);
Serial.print(" %");
Serial.print("\t");
Serial.print("Temperature = ");
Serial.print(temperature);
Serial.println(" C");
delay(1000);
}
