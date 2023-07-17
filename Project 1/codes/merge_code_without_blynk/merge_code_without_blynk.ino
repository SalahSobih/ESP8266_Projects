#include <DHT.h>

//definations of dht11
#define DHTPIN 2          // What digital pin we're connected to
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);
float humidtity,temperature;

// definations of Fan
#define L_Motor_Of_Fan 4
#define R_Motor_Of_Fan 5

// definations of LDR
#define LIGHT_SENSOR_PIN A0 
float percentage_light,analogValue;

// defintions of leds
#define led_1 12
#define led_2 13
#define led_3 14
#define led_4 15

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


void setup() {
   Serial.begin(115200);
   dht.begin();
   pinMode(L_Motor_Of_Fan,OUTPUT);
   pinMode(R_Motor_Of_Fan,OUTPUT);
   pinMode(led_1,OUTPUT);
   pinMode(led_2,OUTPUT);
   pinMode(led_3,OUTPUT);
   pinMode(led_4,OUTPUT);
}

void loop() {
  humidtity = dht.readHumidity();
  temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  if(temperature >= 27.5)
      Fan_ON();
   else 
      Fan_OFF();
      
// reads the input on analog pin (value between 0 and 4095)
  analogValue = analogRead(LIGHT_SENSOR_PIN);
  percentage_light = (analogValue/6.5);
// We'll have a few threshholds, qualitatively determined
  Serial.print("percentage Light = ");
  Serial.print(percentage_light);
  Serial.print(" %");
  if (percentage_light < 10.0) {
    Serial.println(" => Dark");
    open_light();
  } else if (percentage_light < 20.0) {
    Serial.println(" => Dim");
    close_light();
  } else if (percentage_light < 50.0) {
    Serial.println(" => Light");
    close_light();
  } else if (percentage_light < 90.0) {
    Serial.println(" => Bright");
    close_light();
  }
  
  Serial.print("Humidtity = ");
  Serial.print(humidtity);
  Serial.print(" %");
  Serial.print("\t");
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" C");
  delay(1000);
}
