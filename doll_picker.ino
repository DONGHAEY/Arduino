#include <Servo.h>

Servo servo;

void setup() {
  pinMode(8, INPUT_PULLUP);
  
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  
  servo.attach(2);
  servo.write(0);
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  
  if(!digitalRead(8)) {
    servo.write(180);
  } else {
    servo.write(0);
  }
  
  if (x<300) {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
  } else if (x>800) {
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
  }

  if (y<300) {
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
  } else if( y>800) {
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  Serial.println(x);
}
