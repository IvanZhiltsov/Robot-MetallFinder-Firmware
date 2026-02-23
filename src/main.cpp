#include <Arduino.h>
#include <cJSON.h>
#include <BluetoothSerial.h>
#include <string>

BluetoothSerial ESP_BT;
std::string result;
bool is_data = false;

void setup() {
    Serial.begin(9600);
    ESP_BT.begin("ESP32 Bluetooth Test");
}

void loop() {
    char curr_char;

    if (is_data and ESP_BT.available()) {
        curr_char = static_cast<char>(ESP_BT.read());
        if (curr_char == '$') {
            is_data = false;
            cJSON *json_result = cJSON_Parse(result.c_str());
            Serial.println(cJSON_GetObjectItem(json_result, "age")->valueint);
            cJSON_Delete(json_result);
            result.clear();
        }
        else result += curr_char;
    }

    else if (ESP_BT.available()) {
            curr_char = static_cast<char>(ESP_BT.read());
            if (curr_char == '$') is_data = true;
    }
}
