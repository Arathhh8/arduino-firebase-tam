#include "wifiAndFirebaseConfig.h"
#include "cisterns_A.h"

extern NewPing cisterna_1A;
extern NewPing cisterna_2A;
extern NewPing cisterna_3A;

void setup() {
  Serial.begin(115200);

  connectToWiFi();
  connectToFirebase();
}

void loop() {
 
  readAndSendDistance("cisterna1", cistern_1A);
  readAndSendDistance("cisterna2", cistern_2A);
  readAndSendDistance("cisterna3", cistern_3A);
}
