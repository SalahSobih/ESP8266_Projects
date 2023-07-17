#define LIGHT_SENSOR_PIN A0 
float percentage_light,analogValue;
// leds defintions
#define led_1 12
#define led_2 13
#define led_3 14
#define led_4 15


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
  pinMode(led_1,OUTPUT);
  pinMode(led_2,OUTPUT);
  pinMode(led_3,OUTPUT);
  pinMode(led_4,OUTPUT);
}

void loop() {
  // reads the input on analog pin (value between 0 and 4095)
  analogValue = analogRead(LIGHT_SENSOR_PIN);

 // Serial.print("Analog Value = ");
 // Serial.println(analogValue);   // the raw analog reading
  percentage_light = (analogValue/6.5);
  Serial.print("percentage Light = ");
  Serial.print(percentage_light);
  Serial.print(" %");

  // We'll have a few threshholds, qualitatively determined
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
  delay(1000);
}
