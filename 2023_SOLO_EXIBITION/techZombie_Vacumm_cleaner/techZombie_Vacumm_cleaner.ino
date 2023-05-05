/*
 * for Tech-zombie Vacumm cleaner
 * re-write from 
 * https://electricdiylab.com/controlling-n20-encoder-micro-gear-motor-with-arduino/
 * 
 * 2023.04.01 testing GA12-N20 mini DC Motor's encorder
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
volatile int lastEncoded = 0; // Here updated value of encoder store.
volatile long encoderValue = 0; // Raw encoder value

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
  
  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
  
  Serial.begin(9600);
  Serial.println("testing GA12-N20 mini DC Motor's encorder");
}

void loop() {
  R_sensor_value = digitalRead(R_sensor);
  L_sensor_value = digitalRead(L_sensor);
  forword();
//  Serial.print(R_sensor_value);
//  Serial.print(",");
//  Serial.println(L_sensor_value);
//  delay(100);

  if (R_sensor_value == 0){
    motorstop();
    delay(200);  
    digitalWrite(L_IN1, LOW); 
    digitalWrite(L_IN2, HIGH);
    delay(50);
    digitalWrite(R_IN1, HIGH); 
    digitalWrite(R_IN2, LOW);
    delay(2500);
    motorstop();
    delay(200); 
  }
  else if (L_sensor_value == 0){
    motorstop();
    delay(200);
    digitalWrite(L_IN1, LOW); 
    digitalWrite(L_IN2, HIGH);
    delay(50);
    digitalWrite(R_IN1, HIGH); 
    digitalWrite(R_IN2, LOW);
    delay(2500);
    motorstop();
    delay(200); 
  }
  
//  for (int i = 0; i <= 100; i++){
//    digitalWrite(head_IN1, LOW); 
//    digitalWrite(head_IN2, HIGH);
//    Serial.print("Forward  ");
//    Serial.println(encoderValue);
//  }
//
//  motorstop();
//  delay(3000);
//
//  for (int i = 0; i <= 100; i++){
//    digitalWrite(head_IN1, HIGH); 
//    digitalWrite(head_IN2, LOW);
//    Serial.print("Reverse  ");
//    Serial.println(encoderValue);
//  }
//  
//  motorstop();
//  delay(3000);
}

void updateEncoder(){
  int MSB = digitalRead(encoder_IN1); //MSB = most significant bit
  int LSB = digitalRead(encoder_IN2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue --;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue ++;

  lastEncoded = encoded; //store this value for next time
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
