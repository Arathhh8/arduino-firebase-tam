#ifndef CISTERNS_A_H
#define CISTERNS_A_H

#define MAX_DISTANCE 400

#define TRIG_CIS_1A 19
#define ECHO_CIS_1A 18
#define TRIG_CIS_2A 26
#define ECHO_CIS_2A 25
#define TRIG_CIS_3A 33
#define ECHO_CIS_3A 32

#include <NewPing.h>

extern NewPing cistern_1A;
extern NewPing cistern_2A;
extern NewPing cistern_3A;

void readAndSendDistance(const char* cistern_name, NewPing cistern);

#endif
