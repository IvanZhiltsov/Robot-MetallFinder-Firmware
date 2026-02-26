#include <Arduino.h>
#include <MapManager.h>
#include <PinManager.h>
#include <BluetoothSerial.h>
#include <cJSON.h>
#include <string.h>
#include <chrono>
using namespace std::chrono;


BluetoothSerial esp_bt;

bool is_bt_parse = false;
std::string bt_answer;
const char start_parse_symbol = '$';
const char end_parse_symbol = '#';
seconds parse_max_duration = seconds(5);
steady_clock::time_point parse_timeout;


void setup_bluetooth() {
    esp_bt.begin("ESP Bluetooth Test");
    Serial.println("Setup Bluetooth");
}


bool decode_answer(std::string result) {
    if (result.length() == 0) return false;

    cJSON *json_result = cJSON_Parse(result.c_str());
    if (not json_result) cJSON_Delete(json_result); return false;

    cJSON *json_command = cJSON_GetArrayItem(json_result, 0);
    if (not cJSON_IsNumber(json_command)) return false;

    int command = json_command->valueint;
    switch (command) {
        // get map
        case 1: {
            break;
        }

        // set map
        case 2: {
            cJSON *json_map = cJSON_GetArrayItem(json_result, 1);
            if (not cJSON_IsArray(json_map)) return false;

            int map_size = cJSON_GetArraySize(json_map);
            if (map_size < 4) return false;

            float map_array[map_size][2];
            bool is_finish = false;

            for (int i = 0; i < map_size - 1; i++) {
                cJSON* json_cords = cJSON_GetArrayItem(json_map, i);
                cJSON *json_x = cJSON_GetArrayItem(json_cords, 0);
                cJSON *json_y = cJSON_GetArrayItem(json_cords, 1);
                if (not cJSON_IsNumber(json_x) or not cJSON_IsNumber(json_y)) return false;
                float x = json_x->valuedouble;
                float y = json_y->valuedouble;
                map_array[i][0] = x;
                map_array[i][1] = y;
            }

            cJSON *json_finish = cJSON_GetArrayItem(json_map, map_size - 1);
            if (json_finish != NULL) {
                cJSON *json_x = cJSON_GetArrayItem(json_finish, 0);
                cJSON *json_y = cJSON_GetArrayItem(json_command, 1);
                if (not cJSON_IsNumber(json_x) or not cJSON_IsNumber(json_y)) return false;
                float x = json_x->valuedouble;
                float y = json_y->valuedouble;
                map_array[map_size - 1][0] = x;
                map_array[map_size - 1][1] = y;
                is_finish = true;
            }

            set_map(map_size, map_array, is_finish);
            break;
        }

        // clear map
        case 3: {
            break;
        }

        // get info
        case 4: {
            break;
        }

        // get is metal
        case 5: {
            Serial.println(check_metal());
            break;
        }
            
        default: {
            return false;
        }
    }

    return true;
}


bool check_bluetooth() {
    if (esp_bt.connected()) {
        char curr_char;

        if (is_bt_parse) {
            if (steady_clock::now() > parse_timeout) {
                is_bt_parse = false;
                bt_answer.clear();
            }

            else if (esp_bt.available()) {
                curr_char = static_cast<char>(esp_bt.read());
                if (curr_char == start_parse_symbol) {
                    bt_answer.clear();
                    parse_timeout = steady_clock::now() + parse_max_duration;
                }
                else if (curr_char == end_parse_symbol) {
                    is_bt_parse = false;
                    Serial.println(decode_answer(bt_answer));
                    bt_answer.clear();
                }
                else bt_answer += curr_char;
            }
        }

        else if (esp_bt.available()) {
            curr_char = static_cast<char>(esp_bt.read());
            if (curr_char == start_parse_symbol) {
                is_bt_parse = true;
                bt_answer.clear();
                parse_timeout = steady_clock::now() + parse_max_duration;
            }
        }
    }

    else if (is_bt_parse) {
        is_bt_parse = false;
        bt_answer.clear();
    }

    return is_bt_parse;
}
