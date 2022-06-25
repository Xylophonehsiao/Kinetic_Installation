/*
 *            ！！注意左右邊順逆時針問題！！
 *              
 * 2021.09.29 Body Topology hand_part for 右邊
 *            Motor Arduino Code
 *            
 * 2022.06.01 for 2022改           
 * 
 * 2022.06.25 for control without LED
 * 
 * by Xylo Hsiao
 */

const int In1 = 2;      //for LED
const int In2 = 3;
const int In3 = 4;      //for Motor
const int In4 = 5;
const int Motor = 9;   // 600 ~= 5V; 1023 ~=11V
const int LED = 10;
int Maxbright = 255 / 2; //PWM 0 ~ 255
#define handEnd A7
#define signalIN 12
const int handMotor_time = 5000;
int triggerSignal = 0;
int motorState = 0;

void setup() {
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(Motor, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(handEnd, INPUT);
  pinMode(signalIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  analogWrite(Motor, 980);  //900
  analogWrite(LED, 0);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  mstop();
  Serial.begin(9600);
}

void loop() {
  //triggerSignal = Serial.read();
  //Serial.println(analogRead(handEnd));
  triggerSignal = digitalRead(signalIN);
  Auto_home();
  
  if (motorState == 10 && triggerSignal == HIGH){
    tightR();
    delay(500);
  }else if (motorState == 10 && triggerSignal == LOW){
    mstop();
  }

  if (motorState == 10 && analogRead(handEnd) < 700){
    mstop();
    motorState = 11;
  }
  
  if (motorState == 11 && triggerSignal == HIGH){
    releaseL();
    delay(500);
  }else if (motorState == 11 && triggerSignal == LOW){
    digitalWrite(LED_BUILTIN, LOW);
    mstop();
  }

  if (motorState == 11 && analogRead(handEnd) < 700){
    digitalWrite(LED_BUILTIN, LOW);
    mstop();
    motorState = 10;
  }
}

void releaseL(){
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}
void tightL(){
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void tightR(){
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void releaseR(){
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void mstop(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}

void light(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  for (int i = 180; i < 360; i++) {
  float angle = radians(i+90);
  int bright = Maxbright + Maxbright*sin(angle);
  analogWrite(LED, bright);
  delay(5);
  }
}

void goOut(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  for (int i = 0; i < 180; i++) {
  float angle = radians(i+90);
  int bright = Maxbright + Maxbright*sin(angle);
  analogWrite(LED, bright);
  delay(10);
  }
}

void Auto_home(){
  if (triggerSignal == HIGH && motorState == 0){
    digitalWrite(LED_BUILTIN, HIGH);
    light();
    tightR();
    motorState = 1;
  }
  if (analogRead(handEnd) < 700 && motorState ==1){
    digitalWrite(LED_BUILTIN, LOW);
    mstop();
    goOut();
    motorState = 10;
  }
//  if (motorState ==2){
//    light();
//    tightL();
//    delay(handMotor_time);
//    mstop();
//    goOut();
//    motorState = 10;
//  }
}
