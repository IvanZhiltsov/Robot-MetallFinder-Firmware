#include <Arduino.h>
#include <BluetoothManager.h>
#include <PinManager.h>


void setup() {
    Serial.begin(9600);
    Serial.println("Start work");
    setup_Pins();
    setup_bluetooth();
}


void loop() {
    if (not check_bluetooth()) {
        // Serial.println(check_metal());
    }
    delay(10);
}
