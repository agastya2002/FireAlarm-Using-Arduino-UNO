// FireAlarm using DHT11 and LDR

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"
#include<SoftwareSerial.h>
String value;
int TxD = 11;
int RxD = 10;
SoftwareSerial bluetooth(TxD, RxD);

#define buz 7
#define ldr A0
#define red 5
#define DHTPIN 2    

#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(ldr, INPUT);
  pinMode(buz, OUTPUT);
  pinMode(red, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  //float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  //float hic = dht.computeHeatIndex(t, h, false);
  
  int n = analogRead(ldr);
  Serial.print("LDR:");
  Serial.print(n);
  
  Serial.print(F("  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  if(t>=30 && n>=150){
    digitalWrite(red, HIGH);
    digitalWrite(buz, HIGH);
    bluetooth.println("FIRE!!");
  }
  else{
    digitalWrite(red, LOW);
    digitalWrite(buz, LOW);
  }
}
