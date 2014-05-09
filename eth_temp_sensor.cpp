#include "DHT.h"
#include <EtherCard.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x00,0x14,0xA5,0x76,0x19,0x3A  };
static byte myip[] = { 192,168,0,200 };

byte Ethernet::buffer[500];      
BufferFiller bfill;                   

void setup () {
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)
    Serial.println( "Failed to access Ethernet controller");
  ether.staticSetup(myip);
  dht.begin();
}

static word homePage() {
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  bfill = ether.tcpOffset();                        
  bfill.emit_p(PSTR(                               
    "HTTP/1.0 200 OK\r\n"
    "Content-Type: text/xml\r\n"
    "Pragma: no-cache\r\n"
    "\r\n"
    "<?xml version='1.0' encoding='UTF-8'?>\r\n"
    "<sensor>\r\n"
    "<place>Hall</place>\r\n"
    "<temp>$D</temp>\r\n<hum>$D</hum>\r\n"
    "</sensor>"),
      t, h );     
  return bfill.position();                                           
}

void loop () {
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
   
  if (pos)  // check if valid tcp data is received
    ether.httpServerReply(homePage()); // send web page data
}
