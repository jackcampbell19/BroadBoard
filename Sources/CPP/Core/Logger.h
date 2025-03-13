/*
 * Logger (BroadBoard)
 *
 * Created by Jack Campbell on 2/18/25.
 * Copyright (c) 2025 Haku. All rights reserved.
 *
 * Description:
 *     // TODO
*/

#ifndef BROADBOARD_LOGGER_H
#define BROADBOARD_LOGGER_H


namespace Logger {

    class Logger {
    public:
        static void init(uint32_t baudRate);
        static void println(const char* string);
        static void println(const uint8_t v);
        static void println(const uint64_t v);
        static void print(const uint8_t v);
        static void print(const char* string);
    };

}


#endif //BROADBOARD_LOGGER_H
