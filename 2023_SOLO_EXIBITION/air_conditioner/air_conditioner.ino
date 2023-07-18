/*
 * 2023.05.03 for air conditioner's controller
 * 2023.05.06 add for control
 * 
 */

#define IN1     8
#define IN2     9
#define IN3     10
#define IN4     11
#define control 12      //1 go  0 stop
#define light   A0

int light_value = 0;
const int light_gate = 300; //maximum for 3.3V is 500
int light_state = 0;
int control_value = 0;
int control_state = 0;
int pin3_state    = 0;

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
  control_value = digitalRead(control);
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
  light_value = analogRead(light);    // 350 - 500  close < 250
  control_value = digitalRead(control);
//  Serial.print(light_state);
//  Serial.print(" , ");
//  Serial.print(control_value);
//  Serial.print(" ,, ");
//  Serial.println(control_state);
  check_light();
  
  /*  control_value : 1 go | 0 stop
   *  light_state   : 1 open | 0 close
   */
  if (control_state == 0 && control_value == 0){
  //if (control_value == 0){
    check_light();
    if (light_state == 1){
      control_state = 1;
    }
  }
  
  if (control_state == 2 && control_value == 1){
  //if (control_value == 1){
    check_light();
    if (light_state == 0){
      control_state = 3;
    }
  }
  
  if (control_state == 1){
    IN1_pin();
    Serial.println("1");
    control_state = 2;
  }else if (control_state == 3){
    IN1_pin();
    Serial.println("3");
    control_state = 0;
  }

//  if (pin3_state == 0 && light_value > 400){
//    IN3_pin();
//    pin3_state = 1;
//  }else if (pin3_state == 1 && light_value < 400){
//    pin3_state = 0;
//  }
  
}

void check_light(){
  if (light_value > light_gate){
    light_state = 1;
  }else if (light_value <= light_gate){
    light_state = 0;
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
