#include "infrared.h"

IRrecv irrecv(IR_PIN);
decode_results results;

void infrared_avoidance()
{
    int sensor_value = analogRead(SENSOR_PIN);
    if (sensor_value > 500) {
        Serial.println("Object detected!");
        if (irrecv.decode(&results)) {
            Serial.println(results.value, HEX);
            irrecv.resume();
        }
    }
    delay(100);
}