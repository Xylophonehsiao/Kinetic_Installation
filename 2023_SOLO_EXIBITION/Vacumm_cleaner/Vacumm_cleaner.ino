/*
 * for Tech-zombie Vacumm cleaner
 * 
 * 2023.04.01 testing GA12-N20 mini DC Motor's encorder
 * 2023.05.06 for @uitshinn with backwords
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
const long interval = 30000;       //waiting time~~

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
  forword();
  unsigned long currentMillis = millis();
//  Serial.print(R_sensor_value);
//  Serial.print(",");
//  Serial.println(L_sensor_value);
//  delay(100);

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
    delay(2300);
    motorstop();
    delay(200);
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
