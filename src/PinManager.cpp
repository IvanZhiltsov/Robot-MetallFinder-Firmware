#include <Arduino.h>
#include <chrono>
using namespace std::chrono;


const int AvtoMode_Pin = 12;
const int StartBotton = 18;
const int metal_Pin = 2;

const milliseconds metal_cycle_duration = milliseconds(100);
const int control_metal_summa = 1000;


void setup_Pins() {
    pinMode(AvtoMode_Pin, INPUT);
    pinMode(StartBotton, INPUT);
    Serial.println("Setup Pins");
}


bool check_metal() {
    int summa_metal, count_metal = 0;
    steady_clock::time_point metal_end = steady_clock::now() + metal_cycle_duration;
    while (steady_clock::now() < metal_end) {
        summa_metal += analogRead(metal_Pin);
        count_metal++;
        delay(1);
    }
    int result = round(summa_metal / count_metal);
    Serial.println(result);
    if (result > control_metal_summa) return true;
    return false;
}


bool check_AvtoMode_Pin() {
    return digitalRead(AvtoMode_Pin);
}


bool check_StartBotton() {
    return digitalRead(StartBotton);
}
