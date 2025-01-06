#include "RainSensor.h"

// Constructor
RainSensor::RainSensor(uint8_t rxPin, uint8_t txPin) 
    : _rxPin(rxPin), _txPin(txPin) {}

// Initialize UART
void RainSensor::begin(uint32_t baudRate) {
    _serial = &Serial1; // Use HardwareSerial1
    _serial->begin(baudRate, SERIAL_8N1, _rxPin, _txPin);
}

// Check if the sensor is functional
bool RainSensor::isFunctional() {
    uint8_t command[5] = {0x3A, 0x00, 0x00, 0x00, 0x00}; // Firmware query
    command[4] = calculateCRC(command, 4);
    _serial->write(command, 5);

    delay(100); // Give time for the response
    if (_serial->available() >= 5) {
        uint8_t response[5];
        _serial->readBytes(response, 5);
        return (calculateCRC(response, 4) == response[4]);
    }
    return false; // No response or invalid CRC
}

// Check if it is raining
bool RainSensor::isRaining() {
    uint8_t command[5] = {0x3A, 0x01, 0x00, 0x00, 0x0D}; // Query rain status
    _serial->write(command, 5);

    delay(50); // Give time for the response
    if (_serial->available() >= 5) {
        uint8_t response[5];
        _serial->readBytes(response, 5);
        if (calculateCRC(response, 4) == response[4]) {
            return (response[2] != 0); // Non-zero means rain detected
        }
    }
    return false; // Assume no rain if no valid response
}

// CRC-8 calculation
uint8_t RainSensor::calculateCRC(uint8_t *data, uint8_t len) {
    uint8_t crc = 0xFF;
    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc = (crc << 1);
            }
        }
    }
    return crc;
}

