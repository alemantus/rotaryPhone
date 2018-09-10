int startTimer = 0;
unsigned long startTime = 0;
int input = 50;
int count = 0;
int count2 = 0;
int phoneVal = 0;

void setup() {
  Serial.begin(9600);
  pinMode(input, INPUT);
  Serial.println("HELLO");
  attachInterrupt(digitalPinToInterrupt(20), interruptRising, RISING);

}

void loop() {
  phoneVal = analogRead(A0);
  while(digitalRead(input) == HIGH){
    if(count <= 10){
      startTime = millis();
      count++;
      delay(60);
    }
  }

  if((millis()-startTime) > 500){
      if(count!=0){
        if (count == 10){
          count = 0;
        }
        //Serial.println(count);
        count = 0;
        Serial.read();
      }
      startTime = 0;
  }
}

void interruptRising(){
  startTime = millis();
  if(millis()-startTime < 60){
    count2++;
  }
  
    if((millis()-startTime) > 500){
      if(count2!=0){
        if (count2 == 10){
          count2 = 0;
        }
        Serial.println(count2);
        count2 = 0;
        Serial.read();
      }
      startTime = 0;
  }
}



