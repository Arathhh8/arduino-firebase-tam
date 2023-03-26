#include "cisterns_A.h"
#include <FirebaseESP32.h>

// Define Firebase path for the sensor readings
String node = "/SalaA/";

float distance_value = 0.0;
float percentage_value = 0.0;
float last_distance_value = 0.0;

NewPing cistern_1A(TRIG_CIS_1A, ECHO_CIS_1A, MAX_DISTANCE);
NewPing cistern_2A(TRIG_CIS_2A, ECHO_CIS_2A, MAX_DISTANCE);
NewPing cistern_3A(TRIG_CIS_3A, ECHO_CIS_3A, MAX_DISTANCE);

// Define Firebase data object
FirebaseData firebaseData;

// Function to read distance from ultrasonic sensor and send to Firebase
void readAndSendDistance(const char* cistern_name, NewPing cistern) {
  delay(1000);
  
  last_distance_value = distance_value;
  distance_value = cistern.ping_cm();
  percentage_value = map(distance_value, 230, 0, 0, 100);
  
    printf("Distance %s = %f cm\n%f %%\n", cistern_name, distance_value, percentage_value);
    Firebase.setFloat(firebaseData, node + cistern_name, distance_value);
}
