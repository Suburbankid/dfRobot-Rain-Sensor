#ifndef RAIN_SENSOR_H
#define RAIN_SENSOR_H

#include <Arduino.h>

class RainSensor {
public:
    RainSensor(uint8_t rxPin, uint8_t txPin); // Constructor
    void begin(uint32_t baudRate = 115200);   // Initialize UART
    bool isFunctional();                      // Check if the sensor responds
    bool isRaining();                         // Check if it is raining (true = raining, false = not raining)

private:
    uint8_t _rxPin, _txPin;
    HardwareSerial *_serial;
    uint8_t calculateCRC(uint8_t *data, uint8_t len); // CRC-8 calculation
};

#endif

