#include <Arduino.h>
#include <BluetoothManager.h>
#include <GPS_Manager.h>
#include <MapManager.h>
#include <PinManager.h>
#include <AvtoMode.h>

bool is_AvtoMode = false;
bool is_Search = false;

void setup() {
    setup_Pins();
    setup_Bluetooth();
}

void loop() {
    if (not is_Search) {
        check_Bluetooth();
    }

    if (check_AvtoMode_Pin()) {
        is_AvtoMode = true;

        if (check_StartBotton() and is_Map() and is_robot_in_area()) {
            is_Search = true;
        }
    }

    if (is_Search) {
        search();
    }
}
