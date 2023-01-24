#include "VirtualWire.h"

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

void setup() {
  // put your setup code here, to run once:
  vw_set_rx_pin(12); // Set pin 12 as transmitter data pin
  vw_setup(2000); // speed of data transfer Kbps
  pinMode(13,OUTPUT); // Enable pin 13 as output for on board led

  vw_rx_start(); // Start the receiver
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if( vw_get_message(buf,&buflen) ) { // Check for message without blocking program loop
    if( buf[0]=='1' ) { // If a 1 is received, turn on the led
      digitalWrite(13,1);
    } else if( buf[0]=='0' ) { // If a 0 is received, turn off the led
      digitalWrite(13,0);
    }
  }
}
