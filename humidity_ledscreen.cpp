#include "DHT.h"
#include <LiquidCrystal.h>
#include <IRremote.h>

#define DHTPIN 2     
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

int RECV_PIN = 11;
IRrecv irrecv (RECV_PIN);
decode_results results;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600); 
  dht.begin();
  
  irrecv.enableIRIn();
  irrecv.blink13(true);
  
  lcd.begin(16, 2);
  
  
}
void loop() {

  delay(1000);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    lcd.clear ();
    lcd.setCursor(0, 0);
    lcd.print (t);
    lcd.print (" temp");
    lcd.setCursor(0, 1);
    lcd.print (h);
    lcd.print (" humidity");
  }
  
}