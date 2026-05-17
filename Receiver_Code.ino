#include <SoftwareSerial.h>

SoftwareSerial BT(2, 3); // RX, TX

// Motor driver pins
int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

char command;

void setup() {
  BT.begin(9600);
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopCar();
}

void loop() {
  if (BT.available()) {
    command = BT.read();
    Serial.println(command);

    if (command == 'F') {
      forward();
    } 
    else if (command == 'B') {
      backward();
    } 
    else if (command == 'L') {
      left();
    } 
    else if (command == 'R') {
      right();
    } 
    else if (command == 'S') {
      stopCar();
    }
  }
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}