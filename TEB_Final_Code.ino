#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <TinyGPS++.h>
//GPS pins and baud
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
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
  //ss.begin(GPSBaud);
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
  if (cm <= 78 && cm > 0)
  {
    int d = map(cm, 1, 100, 20, 2000);
    digitalWrite(buz, HIGH);
    delay(200);
    digitalWrite(buz, LOW);
    digitalWrite(vibr, HIGH);
    delay(d);
    digitalWrite(vibr, LOW);
    delay(300);
  } else if (cm <= 200 && cm > 78) {
    int d = map(cm, 1, 100, 20, 2000);
    Serial.print("Distance: ");
    digitalWrite(vibr, HIGH);
    delay(d);
    digitalWrite(vibr, LOW);
  }
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
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
    Serial.print("No Connection");
  }
}
