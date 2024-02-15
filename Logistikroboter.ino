#include <AFMotor.h>

AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
AF_DCMotor motor2(2);
AF_DCMotor motor1(1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  String command = "stop";
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    Serial.print("You sent me: ");
    Serial.println(command);
  }
}
