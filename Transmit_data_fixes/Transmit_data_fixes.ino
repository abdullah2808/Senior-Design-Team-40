#include <RadioLib.h>
CC1101 radio = new Module(10, 2, RADIOLIB_NC, 3);
void setup() {
  Serial.begin(9600);

  Serial.print(F("[CC1101] Initializing ... "));
  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void loop() {
  Serial.print(F("[CC1101] Transmitting packet ... "));
  int state = radio.transmit("I am Here!!");
  if (state == RADIOLIB_ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F("success!"));

  } else if (state == RADIOLIB_ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 64 bytes
    Serial.println(F("too long!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }
  delay(500);
}
