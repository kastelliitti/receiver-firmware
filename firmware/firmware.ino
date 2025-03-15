#include "CanSatNeXT.h"

void setup() {
  Serial.begin(115200);
  GroundStationInit(42);
  Serial.println("READY");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() != 0) {
    String input = Serial.readString();
    input.trim();
    int inputInt = input.toInt();
    if (inputInt >= 0 && inputInt < 3) {
      Serial.println("Changing mode to " + (String)inputInt);
      uint8_t dataToSend = inputInt;
      sendData(&dataToSend, 1);
    } else if (inputInt >= 50 && inputInt <= 10000) {
      Serial.println("Changing satellite measurement interval to " + (String)inputInt);
      unsigned short int newInterval = inputInt;
      uint8_t package[2];
      memcpy(&package[0], &newInterval, 2);
      sendData(&package, 2);
    }
  }
}


void onBinaryDataReceived(const uint8_t *data, uint16_t len) {
  if (len == 1) {
    uint8_t num;
    memcpy(&num, data, 1);
    if (num == 42) {
      Serial.print("PRELAUNCH:");
      Serial.println((String)getRSSI());
    } else if (num == 28) {
      Serial.print("STANDBY:");
      Serial.println((String)getRSSI());
    } else {
      Serial.print("UNKNOWN1");
    }
  } else {
    Serial.print("LIVE:");
    Serial.print((String)getRSSI() + ",");
    float values[len/4];
    for (int i = 0; i < len/4; i++) {
      memcpy(&values[i], &data[i * 4], 4);
      Serial.print(String(values[i], 16));
      Serial.print(",");
    }
    Serial.println();
  }
  // } else {
  //   Serial.println("UNKNOWN2");
  // }
}
