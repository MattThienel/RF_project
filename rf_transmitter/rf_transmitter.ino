#include "VirtualWire.h"

uint8_t msg[VW_MAX_MESSAGE_LEN+1];
const unsigned msgLen = VW_MAX_MESSAGE_LEN;

#define GROUP_NUM '0' // Must be a character from 0-9

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  memset(msg, 0, msgLen+1); // Clear msg array
  msg[0] = GROUP_NUM; // Each message starts with group number
  
  pinMode(13,OUTPUT); // Enable pin 13 as output for on board led
  vw_set_tx_pin(12); // Set pin 12 as transmitter data pin
  vw_setup(4000); // speed of data transfer Kbps

  Serial.println("RF transmitter is ready");
  Serial.println("Enter message");
}


void loop() {
  // put your main code here, to run repeatedly:
  int input = Serial.read();
  if( input == -1) return;
  msg[strlen(msg)] = (uint8_t)input;
  
  if( (char)input == '\n' || strlen(msg) == msgLen ) {
    Serial.print("Sending message ");
    Serial.print((char*)&msg[1]);
    vw_send((uint8_t*)msg, strlen(msg));
    digitalWrite(13,1); // Turn on led
    vw_wait_tx(); // Wait until the whole message is done
    digitalWrite(13,0); // Turn off led
    memset(msg, 0, msgLen+1); // Clear msg array for next message
    msg[0] = GROUP_NUM; // Each message starts with group number
  }
   
}
