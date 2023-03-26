#include <WiFi.h>
#include <FirebaseESP32.h>

// Constants for WiFi connection
#define WIFI_SSID "Megacable_2.4G_2C78"
#define WIFI_PASSWORD "paGfeqU7"

// Constants for Firebase connection
#define FIREBASE_HOST "fir-tam-arduino-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "EseNGxrWBBmZd9ydPKWSae6Bh4DPQULxU67RFtW1"

// Function to connect to WiFi
void connectToWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

// Function to connect to Firebase
void connectToFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.println("Firebase connected");
}
