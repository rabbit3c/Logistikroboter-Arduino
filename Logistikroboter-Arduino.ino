#include <AFMotor.h>

AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
AF_DCMotor motor2(2);
AF_DCMotor motor1(1);

int v = 200; //velocity (0 - 255)

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    Serial.println("ok");

    switch (command[0]) { //switch only works with char or int
      case 'v': //velocity (format vXXX)
        v = command.substring(1, 4).toInt();
      case 'f': //forward
        rightForward(v);
        leftForward(v);
        break;
      case 's': //stop
        rightStop();
        leftStop();
        break;
      case 'r': //right
        rightBack(v);
        leftStop();
        break;
      case 'l': //left
        rightStop();
        leftBack(v);
        break;
      default:
        break;
    }
  }
}

void rightForward(int v) {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor1.setSpeed(v);
  motor2.setSpeed(v);
}

void leftForward(int v) {
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  motor3.setSpeed(v);
  motor4.setSpeed(v);
}

void rightBack(int v) {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor1.setSpeed(v);
  motor2.setSpeed(v);
}

void leftBack(int v) {
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  motor3.setSpeed(v);
  motor4.setSpeed(v);
}

void rightStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor1.setSpeed(0);
  motor2.setSpeed(0);
}

void leftStop() {
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}
