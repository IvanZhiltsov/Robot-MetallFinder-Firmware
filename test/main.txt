#include <Arduino.h>
#include <BluetoothManager.h>
#include <GPS_Manager.h>
#include <MapManager.h>
#include <PinManager.h>
#include <AvtoMode.h>


bool is_AvtoMode = false;
bool is_Search = false;


void setup() {
    Serial.begin(9600);
    setup_Pins();
    setup_Bluetooth();
}


void loop() {
    Serial.println("loop");
    delay(500);

    if (not is_Search) {

        if (not check_Bluetooth()) {
            if (check_AvtoMode_Pin()) {
                is_AvtoMode = true;
            }

            if (is_AvtoMode) {
                if (check_StartBotton() and is_Map() and is_robot_in_area()) {
                    is_Search = true;
                }
            }
        }
    }

    else {
        search();
    }
}
