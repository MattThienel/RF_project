#include "VirtualWire.h"

uint8_t msg[VW_MAX_MESSAGE_LEN+1];
uint8_t msgLen = VW_MAX_MESSAGE_LEN;

#define GROUP_NUM '0' // Must be a character from 0-9

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  memset(msg, 0, VW_MAX_MESSAGE_LEN+1); // Clear msg array
  
  vw_set_rx_pin(12); // Set pin 12 as transmitter data pin
  vw_setup(4000); // speed of data transfer Kbps
  pinMode(13,OUTPUT); // Enable pin 13 as output for on board led

  vw_rx_start(); // Start the receiver
  Serial.println("RF receiver is ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if( vw_get_message(msg,&msgLen) ) { // Check for message without blocking program loop
    digitalWrite(13,1); // Turn on led
    if( msg[0] == GROUP_NUM ) {
      Serial.print("Message received from group ");
      Serial.write(msg[0]);
      Serial.print(": ");
      // Print out message
      Serial.print((char*)&msg[1]);
      for( unsigned i = 1; i < msgLen; ++i ) {
        Serial.write(msg[i]);
      }
      if(msg[msgLen] != '\n') {
        Serial.write('\n');
        Serial.write('\r');
      } else if(msg[msgLen-1] != '\r') {
        Serial.write('\r');
      }
    }
    memset(msg, 0, VW_MAX_MESSAGE_LEN+1); // Clear msg array for next message
    msgLen = VW_MAX_MESSAGE_LEN;
    digitalWrite(13,0); // Turn off led
  }
}
