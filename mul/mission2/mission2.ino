#include <TaskScheduler.h>

#define T_LED12 1000
#define T_LED13 2000
#define D_LED13 200
#define T_BUTTON 6000

volatile boolean button_pressed = false;
boolean pressedFirst = true;
boolean LEDstate = false;

void buttonAction();
void LED12Toggle();
void LED13On();
void LED13Off();
void pressed();

Task t0(0, 1, buttonAction);
Task t1(T_LED12, 4, LED12Toggle);
Task t2a(T_LED13, 3, LED13On);
Task t2b(T_LED13, 3, LED13Off);
Scheduler runner;

const int IntLEDPin = 13; // blue
const int ExtLEDPin = 12; // red
const int ButtonPin = 2;

void pressed() {
  button_pressed = true;
  LEDstate = false; // reset whenever the button is pressed... in case of debouncing.
}

void setup() {
  Serial.begin(9600);
  pinMode(IntLEDPin, OUTPUT);
  pinMode(ExtLEDPin, OUTPUT);
  pinMode(ButtonPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ButtonPin), pressed, FALLING);

  runner.init();
  runner.addTask(t0);
  runner.addTask(t1);
  runner.addTask(t2a);
  runner.addTask(t2b);
}

void loop() {
  if (button_pressed) {
    button_pressed = false;
    if (pressedFirst) {
      t0.enable();
    }
    else {
      t0.restart();
    }
  }
  runner.execute();
}

void buttonAction() {
  Serial.println("Button pressed");
  if (pressedFirst) {
    Serial.println("Pressed First");
    t1.enable();
    t2a.enable();
    t2b.enableDelayed(D_LED13);
    pressedFirst = false;
  }
  else {
    t1.restart();
    t2a.restart();
    t2b.restartDelayed(D_LED13);
  }
}

void LED12Toggle() {
  LEDstate = LEDstate ^ 1;
  digitalWrite(ExtLEDPin, LEDstate);
  Serial.println(LEDstate ? "LED12 On" : "LED12 Off");
}

void LED13On() {
  digitalWrite(IntLEDPin, HIGH);
  Serial.println("LED13 On");
}

void LED13Off() {
  digitalWrite(IntLEDPin, LOW);
  Serial.println("LED13 Off");
}
