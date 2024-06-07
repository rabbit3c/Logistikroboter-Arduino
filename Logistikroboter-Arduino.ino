#include <AFMotor.h>

AF_DCMotor motor3(3);
AF_DCMotor motor1(1);

int v = 100; //velocity (0 - 255)

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
        break;
      case 'f': //forward
        rightForward(v);
        leftForward(v);
        break;
      case 's': //stop
        rightStop();
        leftStop();
        break;
      case 'r': //right
        leftForward(v);
        rightBack(180);
        break;
      case 'l': //left
        rightForward(v);
        leftBack(180);
        break;
      case 'b':
        rightBack(v);
        leftBack(v);
      case 't': //turn right or turn left
        if (command == "turn_right") {
            leftForward(230);
            rightBack(150);
        }
        else if (command == "turn_left") {
            rightForward(230);
            leftBack(130);
        }
        break;
      default:
        break;
    }
  }
}

void rightForward(int v) {
  motor1.run(BACKWARD);
  motor1.setSpeed(v);
}

void leftForward(int v) {
  motor3.run(BACKWARD);
  motor3.setSpeed(v);
}

void rightBack(int v) {
  motor1.run(FORWARD);
  motor1.setSpeed(v);
}

void leftBack(int v) {
  motor3.run(FORWARD);
  motor3.setSpeed(v);
}

void rightStop() {
  motor1.run(RELEASE);
  motor1.setSpeed(0);
}

void leftStop() {
  motor3.run(RELEASE);
  motor3.setSpeed(0);
}
