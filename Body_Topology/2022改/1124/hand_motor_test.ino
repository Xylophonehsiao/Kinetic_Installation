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
#define handEnd   A7
#define signalIN1 9      //for release
#define signalIN2 10      //for tight
const int handMotor_time = 5000;
int releaseSignal = 0;
int tightSignal   = 0;
int motorState    = 0;
int ledState      = 0;

void setup() {
  pinMode(In1,      OUTPUT);
  pinMode(In2,      OUTPUT);
  pinMode(In3,      OUTPUT);
  pinMode(In4,      OUTPUT);
  pinMode(handEnd,  INPUT);
  pinMode(signalIN1,    INPUT);
  pinMode(signalIN2,    INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(In1,   LOW);
  digitalWrite(In2,   LOW);
  mstop();
  Serial.begin(9600);
}

void loop() {
  //Serial.println(analogRead(handEnd));
  //Serial.println(motorState);
  releaseSignal = digitalRead(signalIN1);
  tightSignal   = digitalRead(signalIN2);

  if (motorState == 0 && releaseSignal == HIGH){
    Serial.println("re");
      motorState = 1; 
      releaseR();
      light();
      delay(300);
  }else if (motorState != 0 && releaseSignal == HIGH){
    Serial.println("re0");
      motorState = 0;
      mstop();
      delay(500);
  }
  else if (motorState == 0 && tightSignal == HIGH){
    Serial.println("ti");
      motorState = 2;
      tightR();
      light();
      delay(300);
  }else if (motorState != 0 && tightSignal == HIGH){
    Serial.println("ti0");
      motorState = 0;
      mstop();
      delay(500);
  }

  if (analogRead(handEnd) < 700){
    motorState = 0;
    mstop();
    delay(500);
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
