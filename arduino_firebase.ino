#include <NewPing.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#define WIFI_SSID "iPhoneX"
#define WIFI_PASSWORD "01234567"

//#define WIFI_SSID "Megcable_2.4G_96B4"
//#define WIFI_PASSWORD "jackito11"

//#define WIFI_SSID "UlisesF"
//#define WIFI_PASSWORD "z28s5jww"

#define FIREBASE_HOST "fir-tam-arduino-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "EseNGxrWBBmZd9ydPKWSae6Bh4DPQULxU67RFtW1"

FirebaseData firebaseData;

// Define maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500 cm:
#define MAX_DISTANCE 400

#define trigCis_1A 19
#define echoCis_1A 18
#define trigCis_2A 26
#define echoCis_2A 25
#define trigCis_3A 33
#define echoCis_3A 32

// NewPing setup of pins and maximum distance.
NewPing cisterna_1A = NewPing(trigCis_1A, echoCis_1A, MAX_DISTANCE);
NewPing cisterna_2A = NewPing(trigCis_2A, echoCis_2A, MAX_DISTANCE);
NewPing cisterna_3A = NewPing(trigCis_3A, echoCis_3A, MAX_DISTANCE);

String nodo = "/";

void setup() {
  
  Serial.begin(9600);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
      
  Serial.println ("");
  Serial.println ("Se conectó al wifi!");
  Serial.println(WiFi.localIP());
    
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}

void loop() {
  delay(3000);
 
  leerCisterna("cisterna1", cisterna_1A);
  //leerCisterna("cisterna2", cisterna_2A);
  //leerCisterna("cisterna3", cisterna_3A);
}

void leerCisterna(const char* nombre, NewPing cisterna){
  float valor_distancia = cisterna.ping_cm();
  float valorPorcentaje = map(valor_distancia, 230, 0, 0, 100);
  
  Serial.print("Distancia ");
  Serial.print(nombre);
  Serial.print(" = ");
  Serial.print(valor_distancia);
  Serial.println(" cm");
  Serial.print(valorPorcentaje);
  Serial.println(" %");

  Firebase.setFloat(firebaseData, nodo + "/SalaA/" + nombre, valor_distancia);
}
