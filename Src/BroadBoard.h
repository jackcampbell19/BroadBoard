#ifndef BROAD_BOARD_H
#define BROAD_BOARD_H


#include <cstdint>


namespace HAL {

    class OutputPin {
    public:
        OutputPin(uint8_t pin) : pin(pin), value(false) {
            init();
        }

        void set(bool v) {
            value = v;
            setImpl(v);
        }

        void on() {
            set(true);
        }

        void off() {
            set(false);
        }

        bool get() {
            return value;
        }

        void toggle() {
            set(!value);
        }

    private:
        void setImpl(bool v);
        void init();

        uint8_t pin;
        bool value;
    };

    enum class InputResistor {
        PULL_UP,
        PULL_DOWN,
        DISABLED
    };

    class InputPin {
    public:
        InputPin(uint8_t pin, InputResistor resistor = InputResistor::DISABLED) : pin(pin) {
            init(resistor);
        }
        bool read();

        void wait(bool trigger) {
            while (read() != trigger) {}
        }

    private:
        void init(InputResistor resistor);
        uint8_t pin;
    };

    class PWMPin {
    public:

        void setDutyCycle(uint32_t dutyCycle);
        void setFrequency(uint32_t frequency);

    };

    class ADCPin {
    public:
        ADCPin(uint8_t adc) : adc(adc) {
            init();
        }

        uint16_t read();

    private:
        uint8_t adc;

        void init();
    };

    enum class UARTParity {
        NONE
    };

    class UART {
    public:
        UART(uint8_t uart, uint8_t txPin, uint8_t rxPin, uint32_t baud,
             uint32_t dataBits = 8, uint32_t stopBits = 1, UARTParity parity = UARTParity::NONE) : uart(uart), baud(baud) {
            init();
        }

        void read(uint8_t *dst, size_t len);
        void write(uint8_t *src, size_t len);

    private:
        uint8_t uart;
        uint32_t baud;

        void init();
    };

    class Delay {
    public:
        static void milliseconds(uint32_t count);
        static void microseconds(uint64_t count);

        static void seconds(uint32_t count) {
            milliseconds(count * 1000);
        }

        static void minutes(uint32_t count) {
            seconds(count * 60);
        }
    };

    class Timestamp {
    public:
        static uint64_t milliseconds();
        static uint64_t microseconds();
    };

    class Board {
    public:
<BROAD-BOARD-DEFINITIONS>
    };

}


#endif // BROAD_BOARD_H
