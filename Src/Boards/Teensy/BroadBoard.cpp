#include "Arduino.h"
#include "BroadBoard.h"

namespace HAL {

    void OutputPin::setImpl(bool v) {
        digitalWriteFast(pin, v);
    }

    void OutputPin::init() {
        pinMode(pin, OUTPUT);
    }

    void InputPin::init(InputResistor resistor) {

    }

    bool InputPin::read() {
        return 0;
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