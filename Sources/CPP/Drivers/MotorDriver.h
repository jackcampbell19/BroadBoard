//
// Created by Jack Campbell on 10/24/24.
//

#ifndef BETHV2_ELF_MOTORDRIVER_H
#define BETHV2_ELF_MOTORDRIVER_H


#include <cstdint>
#include "Stepper.h"
#include "BroadBoard.h"


template<uint8_t MOTOR_COUNT>
class MotorDriver {
public:
    MotorDriver() = default;

    /**
     * Set a flag to initiate the motor driver.
     */
    void start() {
//        motorLock.aquire(RTOS::Lock::MAX_WAIT_TIME);
        attemptRun = true;
//        motorLock.release();
    }

    bool areAllSteppersAtTarget() {
        for (int i = 0; i < MOTOR_COUNT; ++i) {
            if (!steppers[i].isAtTarget()) {
                return false;
            }
        }
        return true;
    }

    /**
     * Run the motor driver.
     */
    void run() {
//        motorLock.aquire(RTOS::Lock::MAX_WAIT_TIME);
        if (attemptRun) {
            while (!areAllSteppersAtTarget()) {
                uint32_t targetEndCycle = HAL::getCycleCount() + HAL::microsecondsToCycles(1);
                for (int i = 0; i < MOTOR_COUNT; ++i) {
                    stepperTick(steppers[i]);
                }
                while (HAL::getCycleCount() < targetEndCycle) {}
            }
            attemptRun = false;
        }
//        motorLock.release();
    }

protected:
//    RTOS::Lock motorLock;
    bool attemptRun = false;
    Stepper steppers[MOTOR_COUNT];

    static void stepperTick(Stepper &stepper);

};


#endif //BETHV2_ELF_MOTORDRIVER_H
