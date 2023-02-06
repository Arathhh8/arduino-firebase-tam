// Include WiFi.h
#include <NewPing.h>
#include <WiFi.h>

// Include Firebase ESP32 library (this library)
#include <FirebaseESP32.h>

#define WIFI_SSID "Megacable_2.4G_2C78"
#define WIFI_PASSWORD "paGfeqU7"

#define FIREBASE_HOST "fir-tam-arduino-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "EseNGxrWBBmZd9ydPKWSae6Bh4DPQULxU67RFtW1"

FirebaseData firebaseData;

#define pinPot 33
#define trigPin 19
#define echoPin 18

// Define maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500 cm:
#define MAX_DISTANCE 400
// NewPing setup of pins and maximum distance.
NewPing sonar = NewPing(trigPin, echoPin, MAX_DISTANCE);
//termina la configuracion del sensor

int levelPot = 0;
String nodo = "/";
bool iterar = true;
int distanciaSA1 = 0;
float ancho = 3;
float largo = 3;


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
  pinMode(pinPot, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:


  while(iterar){

    Firebase.getInt(firebaseData, nodo + "sensor");
    Serial.println(firebaseData.intData());

    Firebase.getInt(firebaseData, nodo + "temperature");
    Serial.println(firebaseData.stringData());

    iterar = false;
    //Firebase.end(firebaseData);
  }

  levelPot = analogRead(pinPot) * 100 / 4095;
  Serial.println(levelPot);
  delay(1000);
  Firebase.setFloat(firebaseData, nodo + "/temperatureReal/temp", levelPot);
  //Firebase.setFloat(firebaseData, nodo + "temperature", 0);
  sensorValue();


}

void sensorValue(){
  float valor_distancia_1 = sonar.ping_cm();// Leemos la distancia en cm
  float valor_distancia = valor_distancia_1;
  //float valor_distancia = valor_distancia_1*ancho*largo;

  // sensor de distancia en cm

// Measure distance and print to the Serial Monitor:
  Serial.print("Distancia = ");
  // Send ping, get distance in cm and print result (0 = outside set distance range):
  Serial.print(valor_distancia); 
  Serial.println(" Mts3");
  Firebase.setFloat(firebaseData, nodo + "/SalaA/cisterna1", valor_distancia);
}
