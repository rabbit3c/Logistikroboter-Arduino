#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor motor3(3);
AF_DCMotor motor1(1);

Servo servo;

int v = 100; //velocity (0 - 255)

void setup() {
  Serial.begin(9600);
  servo.attach(10);
  servo.write(93);
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
        rightBack(210);
        break;
      case 'l': //left
        rightForward(v);
        leftBack(210);
        break;
      case 'b': //back
        rightBack(v);
        leftBack(v);
      case 't': //turn right or turn left
        if (command == "turn_right") {
            leftForward(230);
            rightBack(150);
        }
        else if (command == "turn_left") {
            rightForward(230);
            leftBack(150);
        }
        break;
      case 'u': //unload (using servo) ur or ul for right and left
        char dir = command[1];
        unload(dir);
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

void unload(char dir) {
  if (dir == 'r') {
    for (int i = 0; i < 10; i++) {
      servo.write(73);
      delay(100);
      servo.write(83);
      delay(100);
    }
  }
  else {
   for (int i = 0; i < 10; i++) {
      servo.write(113);
      delay(100);
      servo.write(103);
      delay(100);
    }
  }
  delay(200);
  servo.write(93);
}
