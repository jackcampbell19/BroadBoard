C_SDK_SOURCE = """

#include "pico/stdlib.h"

namespace HAL {

    void OutputPin::setImpl(bool v) {
        gpio_put(v);
    }
    
    bool InputPin::read() {
        return gpio_get(pin);
    }
    
    
    
}

"""

def generate_pico_w_cpp(config_file):
    pass
