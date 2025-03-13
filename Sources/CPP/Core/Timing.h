/*
 * Timing (BroadBoard)
 *
 * Created by Jack Campbell on 2/18/25.
 * Copyright (c) 2025 Haku. All rights reserved.
 *
 * Description:
 *     // TODO
*/

#ifndef BROADBOARD_TIMING_H
#define BROADBOARD_TIMING_H


namespace Timing {

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

}


#endif //BROADBOARD_TIMING_H
