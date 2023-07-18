/*
 * for Tech-zombie Vacumm cleaner
 * 
 * 2023.04.01 testing GA12-N20 mini DC Motor's encorder
 * 2023.05.06 for @uitshinn with backwords
 * 2023.05.21 timer for 5 mins
 * 
 */

#define head_IN1  4 
#define head_IN2  5
#define R_IN1     6
#define R_IN2     7
#define L_IN1     8
#define L_IN2     9
#define R_sensor  10
#define L_sensor  11

int R_sensor_value = 0;
int L_sensor_value = 0;
int encoder_IN1 = 2;
int encoder_IN2 = 3;
unsigned long previousMillis = 0;
const long interval   = 30000;       //detect time~~
int state = 0;
//unsigned long previousMillis_1 = 0;
////const long interval_1 = 600000;     //10mins
//const long interval_1 = 5000;
unsigned long previousMillis_2 = 0;
//const long interval_2 = 900000;    //15mins
const long interval_2 = 300000;       //5 mins
int timer_state = 0;

void setup() {
  pinMode(head_IN1, OUTPUT);
  pinMode(head_IN2, OUTPUT);
  pinMode(R_IN1, OUTPUT);
  pinMode(R_IN2, OUTPUT);  
  pinMode(L_IN1, OUTPUT);
  pinMode(L_IN2, OUTPUT);
  pinMode(R_sensor, INPUT);  
  pinMode(L_sensor, INPUT);
  pinMode(encoder_IN1, INPUT_PULLUP);
  pinMode(encoder_IN2, INPUT_PULLUP);

  digitalWrite(encoder_IN1, HIGH); //turn pullup resistor on
  digitalWrite(encoder_IN2, HIGH); //turn pullup resistor on
  
  Serial.begin(9600);
  Serial.println("testing GA12-N20 mini DC Motor's encorder");
}

void loop() {
  R_sensor_value = digitalRead(R_sensor);
  L_sensor_value = digitalRead(L_sensor);
    
  timer();
  if (timer_state == 0){
    tatal();
  } else{
    motorstop();
  }
}

void tatal(){
  forword();
  Serial.println("total_run!");
  unsigned long currentMillis = millis();
  //unsigned long currentMillis_1 = millis();
  if (R_sensor_value == 0){
    previousMillis = currentMillis;
    motorstop();
    delay(200);  
    digitalWrite(L_IN1, LOW); 
    digitalWrite(L_IN2, HIGH);
    delay(50);
    digitalWrite(R_IN1, HIGH); 
    digitalWrite(R_IN2, LOW);
    delay(2300);
    motorstop();
    delay(200); 
    previousMillis = currentMillis;
    //previousMillis_1 = currentMillis_1;
  }
  else if (L_sensor_value == 0){
    previousMillis = currentMillis;
    motorstop();
    delay(200);
    digitalWrite(L_IN1, LOW); 
    digitalWrite(L_IN2, HIGH);
    delay(50);
    digitalWrite(R_IN1, HIGH); 
    digitalWrite(R_IN2, LOW);
    delay(2300);
    motorstop();
    delay(200); 
    previousMillis = currentMillis;
    //previousMillis_1 = currentMillis_1;
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    backword();
    delay(5000);
    digitalWrite(L_IN1, LOW); 
    digitalWrite(L_IN2, HIGH);
    delay(50);
    digitalWrite(R_IN1, HIGH); 
    digitalWrite(R_IN2, LOW);
    delay(2500);
    motorstop();
    delay(200);
    previousMillis = currentMillis;
    //previousMillis_1 = currentMillis_1;
  }
}

void timer(){
  unsigned long currentMillis_2 = millis();
  if (currentMillis_2 - previousMillis_2 >= interval_2){
    previousMillis_2 = currentMillis_2;
    //Serial.println("switch_time_state!");
    if (timer_state == 0){
      timer_state = 1;
      Serial.println("switch_time_state_1!");
    } else {
      timer_state = 0;
      Serial.println("switch_time_state_0!");
    }
  }
}

void motorstop(){
  digitalWrite(head_IN1, LOW); 
  digitalWrite(head_IN2, LOW);
  digitalWrite(R_IN1, LOW); 
  digitalWrite(R_IN2, LOW);
  digitalWrite(L_IN1, LOW); 
  digitalWrite(L_IN2, LOW);
}

void backword(){
  digitalWrite(R_IN1, HIGH); 
  digitalWrite(R_IN2, LOW);
  delay(50);
  digitalWrite(L_IN1, HIGH); 
  digitalWrite(L_IN2, LOW);
}

void forword(){
  digitalWrite(R_IN1, LOW); 
  digitalWrite(R_IN2, HIGH);
  delay(50);
  digitalWrite(L_IN1, LOW); 
  digitalWrite(L_IN2, HIGH);
}
