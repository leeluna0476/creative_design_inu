#include <Servo.h>

int pos = 0;
int delay_speed = 30;
Servo myServo;

void runServo() {
  for (pos = 0; pos <= 180; ++pos) {
    myServo.write(pos);
    delay(delay_speed);
  }
  for (pos = 180; pos >= 0; --pos) {
    myServo.write(pos);
    delay(delay_speed);
  }

  Serial.println(delay_speed);
}

void setup() {
  Serial.begin(9600);
  myServo.attach(6, 500, 2500);
  pinMode(7, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  myServo.write(pos);
  runServo();
  delay(100);
}

void loop() {
  int val_pullup_1 = digitalRead(7);
  int val_pullup_2 = digitalRead(4);
  if (!val_pullup_1) {
    delay_speed = (delay_speed + 20) % 100;
    runServo();
  }
  if (!val_pullup_2) {
    delay_speed = (100 + (delay_speed - 20)) % 100;
    runServo();
  }
}
