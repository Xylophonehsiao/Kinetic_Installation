/*
 *            ！！注意左右邊順逆時針問題！！
 *              
 * 2021.09.29 Body Topology hand_part for 右邊
 *            Motor Arduino Code
 *            
 * 2022.06.01 for 2022改           
 * 2022.06.25 for control without LED
 * 2022.10.27 for new installation control by RX480E-4
 * 
 * by Xylo Hsiao
 */

const int In1   = 2;      //for LED
const int In2   = 3;
const int In3   = 4;      //for Motor
const int In4   = 5;
const int Motor = 9;      // 600 ~= 5V; 1023 ~=11V
const int LED   = 10;
int Maxbright   = 255/2;  //PWM 0 ~ 255
#define handEnd   A7
#define signalIN1 11      //for release
#define signalIN2 12      //for tight
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
  pinMode(Motor,    OUTPUT);
  pinMode(LED,      OUTPUT);
  pinMode(handEnd,  INPUT);
  pinMode(signalIN1,    INPUT);
  pinMode(signalIN2,    INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  analogWrite(Motor,  980);  //900
  analogWrite(LED,    0);
  digitalWrite(In1,   LOW);
  digitalWrite(In2,   HIGH);
  mstop();
  Serial.begin(9600);
}

void loop() {
  //Serial.println(analogRead(handEnd));
  releaseSignal = digitalRead(signalIN1);
  tightSignal   = digitalRead(signalIN2);

  if (releaseSignal == HIGH){ 
    releaseR();
    Serial.println("Release");
    if (ledState == 0){
      Serial.println("Go~");
      light();
      ledState = 1;
    }
  }else if (tightSignal == HIGH){ 
      tightR();
      Serial.println("tight");
      if (ledState == 0){
        Serial.println("Go~");
        light();
        ledState = 1;
      }
    }
    
  if (ledState == 1){
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    analogWrite(LED, Maxbright);
    if (releaseSignal == LOW && tightSignal == LOW){
      Serial.println("Stop");
      mstop();
      goOut();
      ledState = 0;
    }
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
