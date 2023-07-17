#define L_motor 4
#define R_motor 5

void setup() {
Serial.begin(115200);
pinMode(L_motor,OUTPUT);
pinMode(R_motor,OUTPUT);
}

void loop() {
digitalWrite(L_motor,HIGH);
digitalWrite(R_motor,LOW);
Serial.println("Fan ON");
delay(4000);
digitalWrite(L_motor,LOW);
digitalWrite(R_motor,LOW);
Serial.println("Fan OFF");
delay(4000);
}
