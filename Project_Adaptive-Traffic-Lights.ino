/*
Adaptive 3-way Traffic Light Control System
*/
int state=1;
//traffic light 1
int red1 = 2;
int yellow1 = 3;
int green1 = 4;
//traffic light 2
int red2 = 5;
int yellow2 = 6;
int green2 = 7;
//traffic light 3
int red3 = 8;
int yellow3 = 9;
int green3 = 10;
//ultra tl1.1
int echo11 = 22;
int trig11 = 23;
//ultra tl1.2
int echo12 = 26;
int trig12 = 27;
//ultra tl2.1
int echo21 = 30;
int trig21 = 31;
//ultra tl2.2
int echo22 = 34;
int trig22 = 35;
//ultra tl3.1
int echo31 = 38;
int trig31 = 39;
//ultra tl3.2
int echo32 = 42;
int trig32 = 43;
//times 3 sec
unsigned long state_time = 0; 
unsigned long delay_state3 = 3000;
//times 15 sec
unsigned long delay_state9 = 9000;
//times saved
unsigned long delay_save = 0;
//range ultrasonic
long durationindigit11, range11;
long durationindigit12, range12;
long durationindigit21, range21;
long durationindigit22, range22;
long durationindigit31, range31;
long durationindigit32, range32;

void state_1();
void state_2();
void state_3();
void state_4();
void state_5();
void state_6();

void setup() {
  Serial.begin(9600);
  //traffic light
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(red3, OUTPUT);
  pinMode(yellow3, OUTPUT);
  pinMode(green3, OUTPUT);
  //ultasonic
  pinMode(echo11, INPUT);
  pinMode(trig11, OUTPUT);
  pinMode(echo12, INPUT);
  pinMode(trig12, OUTPUT);
  pinMode(echo21, INPUT);
  pinMode(trig21, OUTPUT);
  pinMode(echo22, INPUT);
  pinMode(trig22, OUTPUT);
  pinMode(echo31, INPUT);
  pinMode(trig31, OUTPUT);
  pinMode(echo32, INPUT);
  pinMode(trig32, OUTPUT);
}

void loop() {
  //config range ultrasonic
  //ultrasonic 1.1
  digitalWrite(trig11, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig11, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig11, LOW);
  durationindigit11 = pulseIn(echo11, HIGH);
  range11 = (durationindigit11 * 0.034) / 2;   
  //ultrasonic 1.2 
  digitalWrite(trig12, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig12, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig12, LOW);
  durationindigit12 = pulseIn(echo12, HIGH);
  range12 = (durationindigit12 * 0.034) / 2;  
  //ultrasonic 2.1 
  digitalWrite(trig21, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig21, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig21, LOW);
  durationindigit21 = pulseIn(echo21, HIGH);
  range21 = (durationindigit21 * 0.034) / 2;  
  //ultrasonic 2.2
  digitalWrite(trig22, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig22, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig22, LOW);
  durationindigit22 = pulseIn(echo22, HIGH);
  range22 = (durationindigit22 * 0.034) / 2;
  //ultrasonic 3.1
  digitalWrite(trig31, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig31, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig31, LOW);
  durationindigit31 = pulseIn(echo31, HIGH);
  range31 = (durationindigit31 * 0.034) / 2;
  //ultrasonic 3.2
  digitalWrite(trig32, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig32, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig32, LOW);
  durationindigit32 = pulseIn(echo32, HIGH);
  range32 = (durationindigit32 * 0.034) / 2; 
  //state
  switch(state){
  //state 1 (tl1,tl2,tl3)
  //green red red 
  case 1:
    state_1();
    Serial.println("Current time: " + String(delay_state9));
    if((millis()-state_time) < delay_state9-1000){
      if(range21 <= 5){
        if(range22 <= 5){
          Serial.println(delay_save);
          //delay 3 second
          delay_save = 15000;
      }
        else if(range22 > 5){
          delay_save = 12000;
        }
      }
      else{
        delay_save = 9000;
      }
    }
    else if((millis()-state_time) > delay_state9){
      state = 2;
      Serial.println("Time delay saved: " + String(delay_save));
      delay_state9 = delay_save;
      state_time = millis();
    }
    break;
  //state 2 (tl1,tl2,tl3) 
  //yellow yellow red
  case 2:
    state_2();
    if((millis()-state_time) > delay_state3){
      state = 3;
      state_time = millis();
    }
    break;
  //state 3 (tl1,tl2,tl3)
  //red green red
  case 3:
    state_3();
    Serial.println("Current time: " + String(delay_state9));
    if((millis()-state_time) < delay_state9-1000){
      if(range31 <= 5){
        if(range32 <= 5){
          Serial.println(delay_save);
          //delay 3 second
          delay_save = 15000;
      }
        else if(range32 > 5){
          delay_save = 12000;
        }
      }
      else{
        delay_save = 9000;
      }
    }
    else if((millis()-state_time) > delay_state9){
      state = 2;
      Serial.println("Time delay saved: " + String(delay_save));
      delay_state9 = delay_save;
      state_time = millis();
    }
    break;
  //state 4 (tl1,tl2,tl3)
  //red yellow yellow
  case 4:
    state_4();
    if((millis()-state_time) > delay_state3){
      state = 5;
      state_time = millis();
    }
    break;
  //state 5 (tl1,tl2,tl3)
  //red red green
  case 5:
    state_5();
    Serial.println("Current time: " + String(delay_state9));
    if((millis()-state_time) < delay_state9-1000){
      if(range11 <= 5){
        if(range12 <= 5){
          Serial.println(delay_save);
          //delay 3 second
          delay_save = 15000;
      }
        else if(range12 > 5){
          delay_save = 12000;
        }
      }
      else{
        delay_save = 9000;
      }
    }
    else if((millis()-state_time) > delay_state9){
      state = 2;
      Serial.println("Time delay saved: " + String(delay_save));
      delay_state9 = delay_save;
      state_time = millis();
    }
    break;
  //state 6 (tl1,tl2,tl3)
  //yellow red yellow
  case 6:
    state_3();
    if((millis()-state_time) > delay_state3){
      state = 1;
      state_time = millis();
    }
    break;
  }
}

//state 1 (tl1,tl2,tl3)
//green red red 
void state_1(){
  digitalWrite(red1, LOW);
  digitalWrite(red2, HIGH);
  digitalWrite(red3, HIGH);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(yellow3, LOW);
  digitalWrite(green1, HIGH);
  digitalWrite(green2, LOW);
  digitalWrite(green3, LOW); 
}
//state 2 (tl1,tl2,tl3)
//yellow yellow red
void state_2(){
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(red3, HIGH);
  digitalWrite(yellow1, HIGH);
  digitalWrite(yellow2, HIGH);
  digitalWrite(yellow3, LOW);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(green3, LOW);
}
//state 3 (tl1,tl2,tl3)
//red green red
void state_3(){
  digitalWrite(red1, HIGH);
  digitalWrite(red2, LOW);
  digitalWrite(red3, HIGH);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(yellow3, LOW);
  digitalWrite(green1, LOW);
  digitalWrite(green2, HIGH);
  digitalWrite(green3, LOW);
}
//state 4 (tl1,tl2,tl3)
//red yellow yellow
void state_4(){
  digitalWrite(red1, HIGH);
  digitalWrite(red2, LOW);
  digitalWrite(red3, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, HIGH);
  digitalWrite(yellow3, HIGH);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(green3, LOW);
}
//state 5 (tl1,tl2,tl3)
//red red green
void state_5(){
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  digitalWrite(red3, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(yellow3, LOW);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(green3, HIGH);
}
//state 6 (tl1,tl2,tl3)
//yellow red yellow
void state_6(){
  digitalWrite(red1, LOW);
  digitalWrite(red2, HIGH);
  digitalWrite(red3, LOW);
  digitalWrite(yellow1, HIGH);
  digitalWrite(yellow2, LOW);
  digitalWrite(yellow3, HIGH);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(green3, LOW);
}