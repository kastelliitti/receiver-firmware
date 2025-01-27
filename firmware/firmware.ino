#include "CanSatNeXT.h"

void setup() {
  Serial.begin(115200);
  CanSatInit(42);
  Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly:

}

void onDataReceived(String data) {
  Serial.println(data);
}
