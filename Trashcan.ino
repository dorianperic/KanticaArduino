#include <Servo.h>  //Biblioteka za upravljanje servo motorom

Servo servo;      //Deklarirenje servo motora

int pos = 100;      //Početna pozicija servo motora

const int EchoPin = 4;
const int TriggerPin = 6;
const int servo_pin = 9;

bool opened = false;

const int trigger_distance = 15;  //Udaljenost na kojoj se aktivira
const int close_point = 72;       //Pozicija servo motora (zatvorena)
const int open_point = 110;       //Pozicija servo motora (otvorena)

void setup() {
  Serial.begin(9600);
  
  servo.attach(const int servo_pin);
  
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop() {
  int cm = ping(TriggerPin, EchoPin);
  
  Serial.print("Udaljenost: ");
  Serial.println(cm);
  
  delay(50);
}

int ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;
  
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  
  duration = pulseIn(EchoPin, HIGH);
  distanceCm = duration * 10 / 292 / 2;
  
  if (distanceCm <= trigger_distance && opened == false) {
    open();
  }
  else if (distanceCm >= trigger_distance && opened == true) {
    delay(1000);
    close();
  }
  
  return distanceCm;
}

void close() {
  pos = open_point;
  
  if(pos >= close_point){
	pos -= 2;
  	servo.write(pos);
  }
  
  opened = false;
  delay(350);
}

void open() {
  pos = close_point;
  
  if(pos <= open_point){
	pos += 2
  	servo.write(pos);
  }
  
  opened = true;
  delay(350);
}
