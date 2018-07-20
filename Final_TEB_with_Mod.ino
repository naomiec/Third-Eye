
#include <TinyGPS++.h>

//GPS pins and baud
static const int gpsTrig = 4, gpsRX = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
//Back to main code
const int pingTrigPin = 12; //Trigger connected to D12
const int pingEchoPin = 11; //Echo connected to D11
int buz = 4 ; //Buzzer connected to D4
int vibr = 6; //Vibrating Motor connected to D6
void setup() {
  // Initialize serial output.
  Serial.begin(9600);
  Serial.println("Tracking...");
  //Back to main code and GPS setup
  pinMode(buz, OUTPUT);
  pinMode(vibr, OUTPUT);
  pinMode(pingTrigPin, OUTPUT);
  pinMode(pingEchoPin, INPUT);

}
void loop()
{
  long duration, cm;
  pinMode(pingTrigPin, OUTPUT);
  digitalWrite(pingTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingTrigPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(pingTrigPin, LOW);
  pinMode(pingEchoPin, INPUT);
  duration = pulseIn(pingEchoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  if (cm <= 78 && cm > 0)
  {
    int d = map(cm, 1, 100, 20, 2000);
    digitalWrite(buz, HIGH);
    delay(200);
    digitalWrite(buz, LOW);
    delay(200);
    digitalWrite(vibr, HIGH);
    delay(d);
    digitalWrite(vibr, LOW);
  } else if (cm <= 300 && cm > 78) {
    int d = map(cm, 1, 100, 20, 2000);
    digitalWrite(vibr, HIGH);
    delay(d-50);
    digitalWrite(vibr, LOW);
  }
  displayInfo();
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}

long microsecondsToCentimeters(long microseconds)

{
  return microseconds / 14.5;
}
void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print("Lat=");
    Serial.print(gps.location.lat(), 6);
    Serial.print("Lng=");
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print("No Connection     ");
  }
}
