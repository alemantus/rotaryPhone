int startTimer = 0;
unsigned long startTime = 0;
int input = 50;
int count = 0;


void setup() {
  Serial.begin(9600);
  pinMode(input, INPUT);
  Serial.println("HELLO");
}

void loop() {
  
  while(digitalRead(input) == HIGH){
    startTime = millis();
    count++;
    delay(60);
  }

  if((millis()-startTime) > 500){
      if(count!=0){
        if (count == 10){
          count = 0;
        }
        Serial.println(count);
        count = 0;
        Serial.read();
      }
      startTime = 0;
  }
}
