#include <Servo.h>

int pos = 0;
Servo myServo;

void runServo(int button) {
  int p;
  if (button == 1) {
    p = pos;
    pos = (pos + 10) % 180;
    
    for ( ; p < pos; ++p) {
      myServo.write(p);
      delay(15);
    }
  }
  else {
    p = pos;
    pos = (180 + (pos - 10)) % 180;
    
    for ( ; p > pos; --p) {
      myServo.write(p);
      delay(15);
    }
    
  }

  Serial.println(pos);
  
}

void setup() {
  Serial.begin(9600);
  myServo.attach(6, 500, 2500);
  myServo.write(pos);
  pinMode(7, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  delay(100);
}

void loop() {
  /*
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "start") {
      runServo();
    }
  }
  */
  int val_pullup_1 = digitalRead(7);
  int val_pullup_2 = digitalRead(4);
  if (!val_pullup_1) {
    runServo(1);
  }
  if (!val_pullup_2) {
    runServo(2);
  }
}
