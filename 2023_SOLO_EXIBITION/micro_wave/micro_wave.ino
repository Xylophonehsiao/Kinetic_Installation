/*
 * 2023.05.03 for micro wave's controller
 * 
 */

#define IN1     8   //time
#define IN2     9   //6
#define IN3     10  //start
#define IN4     11  //cencel
#define control 12
#define light   A0

int light_value = 0;
const int light_gate = 300; //maximum for 3.3V is 500
int light_state = 0;
int control_state = 0;
int main_state = 0;

void setup() {
  pinMode(IN1,    OUTPUT);
  pinMode(IN2,    OUTPUT);
  pinMode(IN3,    OUTPUT);
  pinMode(IN4,    OUTPUT);
  pinMode(light,  INPUT);
  pinMode(control, INPUT_PULLUP);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  light_value = analogRead(light);
  control_state = digitalRead(control);
  Serial.begin(9600);
  delay(5000);
}

void loop() {
  light_value = analogRead(light);
  control_state = digitalRead(control);
//  Serial.print(light_value);
//  Serial.print(" , ");
//  Serial.println(control_state);
  
//  if (light_value > light_gate){
//    light_state = 1;
//  }else if (light_value <= light_gate){
//    light_state = 0;
//  }
  //if (light_state == 0 && control_state == 0){
  if (control_state == 0 && main_state == 0){
    main_state = 1;
    IN1_pin();
    delay(5000);
    for (int i = 0; i < 3; i++){
      IN2_pin();
      delay(500);
    }
    delay(10000);
    IN3_pin();
  }
  if (control_state == 1){
    main_state = 0;
  }
}

void IN1_pin(){
  digitalWrite(IN1, LOW);
  delay(200);
  digitalWrite(IN1, HIGH);
}

void IN2_pin(){
  digitalWrite(IN2, LOW);
  delay(200);
  digitalWrite(IN2, HIGH);
}

void IN3_pin(){
  digitalWrite(IN3, LOW);
  delay(200);
  digitalWrite(IN3, HIGH);
}

void IN4_pin(){
  digitalWrite(IN4, LOW);
  delay(200);
  digitalWrite(IN4, HIGH);
}
