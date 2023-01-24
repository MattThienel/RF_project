#include "VirtualWire.h"

char *controller;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT); // Enable pin 13 as output for on board led
  vw_set_tx_pin(12); // Set pin 12 as transmitter data pin
  vw_setup(2000); // speed of data transfer Kbps
}

/**
 * Transmit a 1 and turns on led, delaying for 1 second.
 * Then transmit a  0 and turn led off, delay for another second
 * Repeat
 * If receiver is working, both boards should blink in sync at 1 second intervals
 */
void loop() {
  // put your main code here, to run repeatedly:
  // Send '1'
  controller="1";
  vw_send((uint8_t*)controller, strlen(controller)); // Transmit a 1
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13,1); // Turn on led
  delay(1000); // Wait for 1 second

  // Send '0'
  controller="0";
  vw_send((uint8_t*)controller, strlen(controller)); // Transmit a 0
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(13,0); // Turn off led
  delay(1000); // Wait for 1 second
}
