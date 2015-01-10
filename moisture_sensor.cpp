/*
Moisture sensor based on Funduino. 
LED will turn on when soil moisture drop below limit.
*/

int sensor_pin = 0; // the pin that sensor is attached to (analog pin 0)
int led_pin = 10;   // the pin that the LED is attached to

/* Set of sensor values 
Sensor in dry soil   = min   0, max 300
Sensor in humid soil = min 300, max 700
Sensor in water      = min 700, max 950
*/
int moisture_limit1 = 400; 
int moisture_limit2 = 300;
int moisture_limit3 = 200;
int moisture_limit4 = 100;


// Set of LED values = off 0, max 255
int led_on1 = 200;    
int led_on2 = 100;
int led_on3 = 30;
int led_on4 = 5;
int led_off = 0;

void setup() {
    Serial.begin(9600);  // start serial port
}
 
void loop() {
    int moisture = analogRead(sensor_pin);
    Serial.println(moisture); // write sensor data to serial port
    
    if(moisture > moisture_limit1) {
      analogWrite(led_pin, led_off);
        }  
    else if ((moisture < moisture_limit1) && (moisture > moisture_limit2)) {
      analogWrite(led_pin, led_on4);
    }
    else if ((moisture < moisture_limit2) && (moisture > moisture_limit3)) {
      analogWrite(led_pin, led_on3);
    }
    else if ((moisture < moisture_limit3) && (moisture > moisture_limit4)) {
      analogWrite(led_pin, led_on2);
    }
    
    else   {
        analogWrite(led_pin, led_on1);
    }
    delay(5000);
}
