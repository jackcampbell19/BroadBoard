//
// Created by Jack Campbell on 10/9/24.
//

#ifndef BETHV2_STEPPER_H
#define BETHV2_STEPPER_H


#include <cstdint>
#include "GPIO.h"


class Stepper {
public:
    Stepper(GPIO::OutputPin stepPin, GPIO::OutputPin dirPin, uint32_t stepsPerRotation, uint32_t ramp, uint32_t minDelay, uint32_t maxDelay);

    void setTarget(int32_t targetStep);
    [[nodiscard]] bool isAtTarget() const;
    void setTargetIncrement(int32_t increment);
    void reset();


    GPIO::OutputPin stepPin;
    GPIO::OutputPin dirPin;
    uint32_t stepsPerRotation;

    int32_t step = 0;
    int32_t target = 0;
    int32_t targetStartStep = 0;
    bool currentStepPinValue = false;
    uint32_t pulseMicrosecondCounter = 0;

    uint32_t ramp;
    uint32_t minDelay;
    uint32_t maxDelay;

};


#endif //BETHV2_STEPPER_H
