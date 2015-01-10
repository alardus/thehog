/*
Moisture sensor based on Funduino. 
LED will turn on when soil moisture drop below limit.
*/

int sensor_pin = 0; // analog pin 0
int moisture_limit = 300; // the value after the LED will turn on
 
int led_pin = 13;    // the pin that the LED is attached to
int led_on = 255;    // how bright the LED is (0 min, 255 max)
int led_off = 0;     // 

void setup() {
   // Serial.begin(9600);  // start serial port
}
 
void loop() {
    int moisture = analogRead(sensor_pin);
    // Serial.println(moisture); // write sensor data to serial port
    if(moisture < moisture_limit) {
        analogWrite(led_pin, led_on);
        }
    else   {
        analogWrite(led_pin, led_off);
    }
    delay(2000);
}
