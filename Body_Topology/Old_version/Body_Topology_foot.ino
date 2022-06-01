/*
 * 2021.09.29 Body Topology foot_part 
 *            LED & Motor Arduino Code
 *            
 * 2021.11.15 Body Topology foot_part           
 *            for NTT LabX
 * by Xylo Hsiao
 */

const int In1 = 2; //LED
const int In2 = 3; //LED
const int In3 = 4; //
const int In4 = 5;
const int Motor = 9;
const int LED = 10;  // 600 ~= 5V; 1023 ~=11V
int Maxbright = 255 / 2; //PWM 0 ~ 255
#define footEnd A7
#define signalIN 12
const int footMotor_time = 25000;  //25000
int triggerSignal = 0;
int motorState = 0;

void setup() {
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(Motor, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(signalIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  analogWrite(LED, 0);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  mstop();
  Serial.begin(9600);
}

void loop() {
  triggerSignal = digitalRead(signalIN);
  //Serial.println(triggerSignal);
  digitalWrite(LED_BUILTIN, LOW);
  
  if (triggerSignal == HIGH && motorState == 0){     //49 for keybroad"1"
    digitalWrite(LED_BUILTIN, HIGH);
    mstop();
    light();
    front();
    delay(footMotor_time);
    mstop();
    goOut();
    motorState = 1;
  }
  if (triggerSignal == LOW && motorState == 1){     //50 for keybroad"2"
    light();
    back();
    motorState = 2;
  }
  if (analogRead(footEnd) > 900 && motorState == 2){
    mstop();
    delay(200);
    front(); 
    delay(100);
    mstop();
    goOut();
    motorState = 0;
  }
}

void light(){
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  for (int i = 180; i < 360; i++) {
  float angle = radians(i+90);
  int bright = Maxbright + Maxbright*sin(angle);
  Serial.println(bright);
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
  Serial.println(bright);
  analogWrite(LED, bright);
  delay(10);
  }
}

void back(){
  digitalWrite(Motor, HIGH);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
}

void front(){
  digitalWrite(Motor, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
}

void mstop(){
  digitalWrite(Motor, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
}
