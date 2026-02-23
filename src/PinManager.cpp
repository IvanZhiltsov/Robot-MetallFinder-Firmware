#include <Arduino.h>


int AvtoMode_Pin = 12;
int StartBotton = 18;


void setup_Pins() {
    pinMode(AvtoMode_Pin, INPUT);
    pinMode(StartBotton, INPUT);
}


bool check_AvtoMode_Pin() {
    return digitalRead(AvtoMode_Pin);
}


bool check_StartBotton() {
    return digitalRead(StartBotton);
}
