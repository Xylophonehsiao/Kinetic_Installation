/*
 * for moving skin
 * 2023.04.15 begin
 * 
 */

#define butt        A2
#define butt_end1   A6
#define butt_end2   A7
#define motor_power 2
#define motor_turn  3

int axis_value  = 0;
int medd_value  = 0;
int butt_value  = 0;
int end1_value  = 0;
int end2_value  = 0;
int power_value = 0; //for input

void setup() {
  pinMode(butt, INPUT);
  pinMode(motor_power, OUTPUT);
  pinMode(motor_turn, OUTPUT);
  pinMode(butt_end1, INPUT_PULLUP);
  pinMode(butt_end2, INPUT_PULLUP);
  Serial.begin(9600);
  butt_value = digitalRead(butt);
  end1_value = analogRead(butt_end1);
  end2_value = analogRead(butt_end2);
  //power_value = digitalRead(motor_power);
  if (end1_value > 100){
    digitalWrite(motor_turn, HIGH);
  }else if(end2_value > 100){
    digitalWrite(motor_turn, LOW);
  }else if (end2_value == 0 && end1_value == 0){
    digitalWrite(motor_turn, HIGH);
  }
}

void loop() {
  butt_value = digitalRead(butt);
  end1_value = analogRead(butt_end1);
  end2_value = analogRead(butt_end2);
  //test_value();
  
  if (end1_value > 100){
    digitalWrite(motor_turn, HIGH);
    delay(1000);
    Serial.println("motor_turn1");
  }else if(end2_value > 100){
    digitalWrite(motor_turn, LOW);
    delay(1000);
    Serial.println("motor_turn2");
  }
}

void test_value(){
  Serial.print(butt_value);
  Serial.print(",");
  Serial.print(end1_value);
  Serial.print(",");
  Serial.println(end2_value);
  delay(100);
}

