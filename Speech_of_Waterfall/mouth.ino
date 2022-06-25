#include <Servo.h>

Servo myservo;
int pos = 0;

void setup() {
  myservo.attach(9);
}

void loop() {
  for (pos = 50; pos <= 170; pos += 1) {
    myservo.write(pos);
    delay(3);
  }
  for (pos = 170; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(5);
  }
}
