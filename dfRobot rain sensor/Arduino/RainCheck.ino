#include <RainSensor.h>

// Initialize the sensor object with RX and TX pins
RainSensor rainSensor(16, 17); // RX = GPIO16, TX = GPIO17

void setup() {
    Serial.begin(115200);
    rainSensor.begin();

    if (!rainSensor.isFunctional()) {
        Serial.println("Sensor is not functional! Check connections.");
        while (true); // Stop execution
    }
    Serial.println("Sensor is ready. Checking rain status...");
}

void loop() {
    bool raining = rainSensor.isRaining();
    if (raining) {
        Serial.println("It is raining.");
    } else {
        Serial.println("No rain detected.");
    }
    delay(1000); // Check every second
}

