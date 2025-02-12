#include "Arduino.h"
#include "BroadBoard.h"

namespace HAL {

    void Logger::init(uint32_t baudRate) {
        Serial.begin(baudRate);
    }

    void Logger::println(const char* string) {
        Serial.println(string);
    }

    void Logger::println(const uint8_t v) {
        Serial.println(v);
    }

    void Logger::println(const uint64_t v) {
        Serial.println(v);
    }

    void Logger::print(const char* string) {
        Serial.print(string);
    }

    void Logger::print(const uint8_t v) {
        Serial.print(v);
    }

    void OutputPin::setImpl(bool v) {
        digitalWriteFast(pin, v);
    }

    void OutputPin::init() {
        pinMode(pin, OUTPUT);
    }

    void InputPin::init(InputResistor resistor) {
        if (resistor == InputResistor::PULL_UP) {
            pinMode(pin, INPUT_PULLUP);
        } else if (resistor == InputResistor::PULL_DOWN) {
            pinMode(pin, INPUT_PULLDOWN);
        } else {
            pinMode(pin, INPUT);
        }
    }

    bool InputPin::read() {
        return digitalReadFast(pin);
    }

    void PWMPin::setDutyCycle(uint32_t dutyCycle) {}
    void PWMPin::setFrequency(uint32_t frequency) {}

    void ADCPin::init() {

    }

    uint16_t ADCPin::read() {
        return 0;
    }

    void Delay::milliseconds(uint32_t count) {
         delayMicroseconds(count * 1000);
    }

    void Delay::microseconds(uint64_t count) {
        delayMicroseconds(count);
    }

    uint64_t Timestamp::milliseconds() {
        return 0;
    }

    uint64_t Timestamp::microseconds() {
        return 0;
    }

}