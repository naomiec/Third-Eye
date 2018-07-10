
  const int pingTrigPin = 12; //Trigger connected to D12
  const int pingEchoPin = 11; //Echo connected to D11
  int buz = 4 ; //Buzzer connected to D4
  int led = 2; //Led connected to D2
  int vibr = 6; //Vibrating Motor connected to D6
  void setup() {
    Serial.begin(9600);
    pinMode(buz, OUTPUT);
    pinMode(led, OUTPUT);
    pinMode(vibr, OUTPUT);
  }
  void loop()
  {
    long duration, cm;
    pinMode(pingTrigPin, OUTPUT);
    digitalWrite(pingTrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingTrigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingTrigPin, LOW);
    pinMode(pingEchoPin, INPUT);
    duration = pulseIn(pingEchoPin, HIGH);
    cm = microsecondsToCentimeters(duration);
     if(cm<=150 && cm>0)
     {
      int d= map(cm, 1, 100, 20, 2000);
      digitalWrite(led, HIGH);
      delay(100);
      delay(d);
      digitalWrite(buz, HIGH);
      delay(300);
      digitalWrite(buz,LOW);
      digitalWrite(vibr,HIGH);
      delay(300);
      digitalWrite(vibr,LOW);
    } else {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      delay(100);
    }
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    delay(100);
    }

 long microsecondsToCentimeters(long microseconds)
 {
 return microseconds /29/2;
 }
