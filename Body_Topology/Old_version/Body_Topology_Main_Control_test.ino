/*         
 * 2021.09.24 Body Topology Main Control & Airpump
 *            Arduino Code
 * 2021.09.29 新增，頸部LED不用重新斷電即可重開
 * by Xylo Hsiao
 */

int Maxbright = 255 / 2; //PWM 0 ~ 255
#define handR 2
#define handL 4
#define footR 3
#define footL 5
#define signalIN A7
int triggerSignal = 0;
int motorState = 0;
const int airPump_time = 25000;  //25000
int state1, state2, state3, state4;
int button1, button2, button3, button4;
const int button_time = 200;

void setup() {
  pinMode(handR, OUTPUT);
  pinMode(handL, OUTPUT);  
  pinMode(footR, OUTPUT);
  pinMode(footL, OUTPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);  
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  digitalWrite(handR, LOW);
  digitalWrite(handL, LOW);
  digitalWrite(footR, LOW);
  digitalWrite(footL, LOW);
  Serial.begin(9600);
  motorState == 0;
  state1 = 0;
  state2 = 0;
  state3 = 0;
  state4 = 0;
  Serial.println("LabX ready!!");
}

void loop() {
  //triggerSignal = Serial.read();
  readpin();
//  Serial.print(button1);
//  Serial.print(", ");
//  Serial.print(button2);
//  Serial.print(", ");
//  Serial.print(button3);
//  Serial.print(", ");
//  Serial.println(button4);
  
  //if (triggerSignal == 49 && state1 == 0){     //49 for keybroad"1"
  if (button1 == HIGH && state1 == 0){
    digitalWrite(handR, HIGH);
    Serial.println("> handR O!!");
    triggerSignal = 0;
    state1 = 1;
    delay(button_time);
    readpin();
  }
  //if (triggerSignal == 49 && state1 == 1){     //50 for keybroad"2"
  if (button1 == HIGH && state1 == 1){
    digitalWrite(handR, LOW);
    Serial.println("< handR X!");
    triggerSignal = 0;
    state1 = 0;
    delay(button_time);
    readpin();
  }
  //if (triggerSignal == 50 && state2 == 0){     //keybroad"3"
  if (button2 == HIGH && state2 == 0){
    digitalWrite(handL, HIGH);
    Serial.println(">> handL O!!");
    triggerSignal = 0;
    state2 = 1;
    delay(button_time);
    readpin();
  }
  //if (triggerSignal == 50 && state2 == 1){     //keybroad"4"
  if (button2 == HIGH && state2 == 1){
    digitalWrite(handL, LOW);
    Serial.println("<< handL X!");
    triggerSignal = 0;
    state2 = 0;
    delay(button_time);
    readpin();
  }
  //if (triggerSignal == 51 && state3 == 0){     //keybroad"5"
  if (button3 == HIGH && state3 == 0){
    digitalWrite(footR, HIGH);
    Serial.println(">>> footR O!!");
    triggerSignal = 0;
    state3 = 1;
    delay(button_time);
    readpin();
  }
  //if (triggerSignal == 51 && state3 == 1){     //keybroad"6"
  if (button3 == HIGH && state3 == 1){
    digitalWrite(footR, LOW);
    Serial.println("<<< footR X!");
    triggerSignal = 0;
    state3 = 0;
    delay(button_time);
    readpin();
  }
  //if (triggerSignal == 52 && state4 == 0){     //keybroad"7"
  if (button4 == HIGH && state4 == 0){
    digitalWrite(footL, HIGH);
    Serial.println(">>>> footL O!!");
    triggerSignal = 0;
    state4 = 1;
    delay(button_time);
    readpin();
  }
  //if (triggerSignal == 52 && state4 == 1){     //keybroad"8"
  if (button4 == HIGH && state4 == 1){
    digitalWrite(footL, LOW);
    Serial.println("<<<< footL X!");
    triggerSignal = 0;
    state4 = 0;
    delay(button_time);
    readpin();
  }
}

void readpin(){
  button1 = digitalRead(9);    // hand R
  button2 = digitalRead(12);   // foot L
  button3 = digitalRead(11);   // foot R
  button4 = digitalRead(10);   // hand L
}
