#include <RainSensor.h>

// Initialize the sensor object with RX and TX pins
RainSensor rainSensor(16, 17); // RX = GPIO16, TX = GPIO17

void setup() {
    Serial.begin(115200);
    rainSensor.begin();

    Serial.println("Checking sensor functionality...");
    if (rainSensor.isFunctional()) {
        Serial.println("Sensor is functional!");
    } else {
        Serial.println("Sensor is not responding. Check connections.");
    }
}

void loop() {
    // Nothing to do here for this test
}

