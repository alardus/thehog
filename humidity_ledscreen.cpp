#include "DHT.h"
#include <LiquidCrystal.h>

DHT dht;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);
  dht.setup(2);

  lcd.begin(16, 2);
  lcd.print ("climate meter");
}

void loop() {
  delay(1000);

  float h = dht.getHumidity();
  float t = dht.getTemperature();

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
