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
  static float signal_strength = 0;
  static float max_strength = -1000; 
  static int angle = 0;
  static int max_angle = 0;
  static int counter = 0;
  Serial.print(F("[CC1101] Waiting for incoming transmission ... "));
  // you can receive data as an Arduino String
  String str;
  int state = radio.receive(str);
  delay(2000);
  if (state == RADIOLIB_ERR_NONE) {
    // packet was successfully received
    Serial.println(F("success!"));

//    // print the data of the packet
//    Serial.print(F("[CC1101] Data:\t\t"));
//    Serial.println(str);

    Serial.print(F("[CC1101] RSSI:\t\t"));
    Serial.print(radio.getRSSI());
    Serial.println(F(" dBm"));
    
  } else if (state == RADIOLIB_ERR_RX_TIMEOUT) {
    // timeout occurred while waiting for a packet
    Serial.println(F("timeout!"));

  } else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
    // packet was received, but is malformed
    Serial.println(F("CRC error!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }
  signal_strength = radio.getRSSI();
  if(signal_strength >= max_strength)
  {
    max_strength = signal_strength;
    max_angle = angle;
    }
  counter += 1;
  angle += 4;
  if(counter >= 46)
  {
    Serial.print("Max Signal Strength: ");
    Serial.println(max_strength);
    Serial.print("Max Angle: ");
    Serial.println(max_angle); 
    delay(1000*100);   
    exit(0);
    }
}
