#include <NewPing.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// Constants for WiFi connection
#define WIFI_SSID "Megacable_2.4G_2C78"
#define WIFI_PASSWORD "paGfeqU7"

// Constants for Firebase connection
#define FIREBASE_HOST "fir-tam-arduino-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "EseNGxrWBBmZd9ydPKWSae6Bh4DPQULxU67RFtW1"

// Define maximum distance we want to ping for (in centimeters).
// Maximum sensor distance is rated at 400-500 cm.
#define MAX_DISTANCE 400

// Define pins for ultrasonic sensors
#define TRIG_CIS_1A 19
#define ECHO_CIS_1A 18
#define TRIG_CIS_2A 26
#define ECHO_CIS_2A 25
#define TRIG_CIS_3A 33
#define ECHO_CIS_3A 32

// Define Firebase path for the sensor readings
String nodo = "/SalaA/";

// Define Firebase data object
FirebaseData firebaseData;

// Define ultrasonic sensor objects
NewPing cisterna_1A(TRIG_CIS_1A, ECHO_CIS_1A, MAX_DISTANCE);
NewPing cisterna_2A(TRIG_CIS_2A, ECHO_CIS_2A, MAX_DISTANCE);
NewPing cisterna_3A(TRIG_CIS_3A, ECHO_CIS_3A, MAX_DISTANCE);
float valor_distancia = 0.0;

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

// Function to read distance from ultrasonic sensor and send to Firebase
void readAndSendDistance(const char* nombre, NewPing cisterna) {
  float valor_distancia_anterior = valor_distancia;
  valor_distancia = cisterna.ping_cm();
  float valorPorcentaje = map(valor_distancia, 230, 0, 0, 100);
  
  if (abs(valor_distancia - valor_distancia_anterior) > 10) {
    Serial.println("Measurement discarded due to maximum difference.");
    Serial.println(valor_distancia);
  } else {
    printf("Distance %s = %f cm\n%f %%\n", nombre, valor_distancia, valorPorcentaje);
    Firebase.setFloat(firebaseData, nodo + nombre, valor_distancia);
  }
}

void setup() {
  Serial.begin(115200);

  connectToWiFi();
  connectToFirebase();
}

void loop() {
  delay(3000);
 
  //readAndSendDistance("cisterna1", cisterna_1A);
  //readAndSendDistance("cisterna2", cisterna_2A);
  readAndSendDistance("cisterna3", cisterna_3A);
}
