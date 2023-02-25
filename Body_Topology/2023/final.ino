/*           
 *            ！！注意左右邊順逆時針問題！！
 *            analogRead(handEnd) < 700
 *              
 * 2021.09.29 Body Topology hand_part for 右邊
 *            Motor Arduino Code
 *            
 * 2022.06.01 for 2022改           
 * 2022.06.25 for control without LED
 * 2022.10.27 for new installation control by RX480E-4
 * 2022.11.24 for battary and mini 2-ch H-bridge module  
 *            testing control 5V LED (PWM no use?)
 * 2023.01.10 for magnet feedback control 
 *            (1023 no magnet, other is magnet)
 * 2023.01.30 control by push botton one time
 * 2023.02.14 fix the length, about 35cm (5 turns for drum)
 *            
 * This version is for 5V LED & 12V DC Motor 
 * with battary and RX480E-4 (wireless control)
 * 
 * by Xylo Hsiao
 * 
 * Fucking body & ...
 */

const int In1   = 2;      //for LED
const int In2   = 3;
const int In3   = 4;      //for Motor
const int In4   = 5;
#define magnet    A7     //正式：A7
#define signalIN1 9      //for release
#define signalIN2 10     //for tight
int motorStep     = 0;
const int maxStep = 5;
int releaseSignal = 0;
int tightSignal   = 0;
int motorState    = 0;
int motor_butt    = 0;
int magnetState   = 0;
int mag_butt      = 0;
int ledState      = 0;
int button1       = 0;
int button2       = 0;

void setup() {
  pinMode(In1,      OUTPUT);
  pinMode(In2,      OUTPUT);
  pinMode(In3,      OUTPUT);
  pinMode(In4,      OUTPUT);
  pinMode(magnet,       INPUT);
  pinMode(signalIN1,    INPUT);
  pinMode(signalIN2,    INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(In1,   LOW);
  digitalWrite(In2,   LOW);
  mstop();
  Serial.begin(9600);
  Serial.println("control ver.2023.02.14");
  Serial.println("please power off when the longest length!!");
}

void loop() {
//  Serial.print(digitalRead(signalIN1));
//  Serial.print(",");
//  Serial.println(digitalRead(signalIN2));
  //Serial.println(analogRead(magnet));
  magnetCount();
  buttonCount();
  counting_magnet();
  releaseSignal = maxStep - motorStep;
  delay(50);
  
  if (releaseSignal > 0 && motor_butt == 1){
    //Serial.println("1-1");
    tightR();
    light();
    delay(100);
  }else if (motorStep > 0 && motor_butt == 2){
    //Serial.println("2-1");
    releaseR();
    light();
    delay(100);
  }else if (button1 == 0 || button2 == 0){
    counting_magnet();
    if (analogRead(magnet) < 700){
      //delay(100);
      //Serial.println("s");
      mstop();
      motor_butt = 0;
    }
  }
}

void magnetCount(){
  if (motorStep == maxStep && motorState == 0){
    motorState = 1;
    mstop();
  }else if (motorStep == 0 && motorState == 1){
    motorState = 0;
    mstop();
  }
}

void counting_magnet(){
  if (analogRead(magnet) > 700 && magnetState == 0){
    magnetState = 1;
  }else if(analogRead(magnet) < 700 && magnetState == 1){
    magnetState = 0;
    if (mag_butt == 1){
      motorStep ++;
    }else if (mag_butt == 2){
      motorStep --;
    }
    Serial.println(motorStep);
  }
  if (motorStep < 0){
    mstop();
  }else if (motorStep > maxStep){
    mstop();
  }
}

void buttonCount(){
  if (digitalRead(signalIN1) == 1 && button1 == 0){
    button1 = 1;
    mag_butt = 1;
    motor_butt = 1;
    delay(100);
  }else if (digitalRead(signalIN1) == 0 && button1 == 1){
    button1 = 0;
  }
  if (digitalRead(signalIN2) == 1 && button2 == 0){
    button2 = 1;
    mag_butt = 2;
    motor_butt = 2;
    delay(100);
  }else if (digitalRead(signalIN2) == 0 && button2 == 1){
    button2 = 0;
  }
}

void tightR(){
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}
void releaseR(){
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void light(){
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
}
void goOut(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
}

void mstop(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
