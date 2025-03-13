//
// Created by Jack Campbell on 10/9/24.
//

#include "Stepper.h"


Stepper::Stepper(GPIO::OutputPin stepPin, GPIO::OutputPin dirPin, uint32_t stepsPerRotation, uint32_t ramp, uint32_t minDelay, uint32_t maxDelay) :
        stepPin(stepPin),
        dirPin(dirPin),
        stepsPerRotation(stepsPerRotation),
        ramp(ramp),
        minDelay(minDelay),
        maxDelay(maxDelay) {}


bool Stepper::isAtTarget() const {
    return step == target;
}


void Stepper::setTarget(int32_t targetStep) {
    targetStartStep = step;
    target = targetStep;
}

void Stepper::setTargetIncrement(int32_t increment) {
    setTarget(target + increment);
}

void Stepper::reset() {
    step = 0;
    target = 0;
    targetStartStep = 0;
    pulseMicrosecondCounter = 0;
}