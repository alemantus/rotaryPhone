int A = 10;
int B = 11;
int pwm = 9;
int startTimer = 0;
unsigned long startTime = 0;
int input = 2;
int count = 0;
String number = "";
int hangUp = 7;

void setup() {
  Serial.begin(9600);
  pinMode(hangUp, INPUT);
  pinMode(input, INPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(pwm, OUTPUT);
  Serial.println("HELLO");
  
}

void loop() {

  while (digitalRead(input) == HIGH) {
    startTime = millis();
    count++;
    delay(55);
  }

  if ((millis() - startTime) > 500) {
    if (count != 0) {
      if (count >= 10) {
        count = 0;
      }
      number += String(count);
      count = 0;
      Serial.read();
      if (number.length() >= 8) {
        Serial.println(number);
        number = "";
      }
    }
    startTime = 0;
  }
  if (digitalRead(hangUp) == HIGH) {
    number = "";
    Serial.println(76);
    delay(200);
  }
  if (Serial.available() > 0) {
    if (String(Serial.read()) == "ring"){
      Serial.println("MODtaget");
      ring();
      delay(500);
      ring();
    }
  }
  
}

void ring(){
  int startTime = millis();
  while(millis-startTime < 1000){
  digitalWrite(pwm, HIGH);
  
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  delay(40);
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  delay(40);
  }
}


