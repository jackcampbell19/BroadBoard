#include "pico/stdlib.h"

namespace HAL {

    void OutputPin::setImpl(bool v) {
        gpio_put(pin, v);
    }

    void OutputPin::init() {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
    }

    void InputPin::init(InputResistor resistor) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        if (resistor == InputResistor::PULL_UP) {
            gpio_pull_up(pin);
        } else if (resistor == InputResistor::PULL_DOWN) {
            gpio_pull_down(pin);
        }
    }

    bool InputPin::read() {
        return gpio_get(pin);
    }

    void PWMPin::setDutyCycle(uint32_t dutyCycle) {}
    void PWMPin::setFrequency(uint32_t frequency) {}

    void ADCPin::init() {
        adc_init();
    }

    uint16_t ADCPin::read() {
        adc_select_input(adc);
        return adc_read();
    }

    void Delay::milliseconds(uint32_t count) {
         sleep_ms(delay);
    }

    void Delay::microseconds(uint64_t count) {
        sleep_us(delay);
    }

    uint64_t Timestamp::milliseconds() {
        return time_us_64() / 1000;
    }

    uint64_t Timestamp::microseconds() {
        return time_us_64();
    }

}