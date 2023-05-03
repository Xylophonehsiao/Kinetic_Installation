/*
 * 2023.05.03 for air conditioner's controller
 * 
 */

#define IN1     8
#define IN2     9
#define IN3     10
#define IN4     11
#define control 12
#define light   A0

int light_value = 0;
const int light_gate = 300; //maximum for 3.3V is 500
int light_state = 0;
int control_state = 0;

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
  for (int i = 0; i < 10; i++){
    delay(500);
    IN2_pin();
  }
  if (light_value <= light_gate){
    delay(1000);
    IN1_pin();
  }
}

void loop() {
  light_value = analogRead(light);
  control_state = digitalRead(control);
//  Serial.print(light_value);
//  Serial.print(" , ");
//  Serial.println(control_state);
  
  if (light_value > light_gate){
    light_state = 1;
  }else if (light_value <= light_gate){
    light_state = 0;
  }
  if (light_state == 0 && control_state == 0){
    IN1_pin();
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
