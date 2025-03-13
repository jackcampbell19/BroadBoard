//
// Created by Jack Campbell on 10/24/24.
//

#include "MotorDriver.h"


void MotorDriver<3>::run() {
    motorLock.aquire(RTOS::Lock::MAX_WAIT_TIME);
    if (attemptRun) {
        while (!stepperA.isAtTarget() || !stepperB.isAtTarget() || !stepperC.isAtTarget()) {
            uint32_t targetEndCycle = HAL::getCycleCount() + HAL::microsecondsToCycles(1);
            stepperTick(stepperA);
            stepperTick(stepperB);
            stepperTick(stepperC);
            while (HAL::getCycleCount() < targetEndCycle) {}
        }
        attemptRun = false;
    }
    motorLock.release();
}

uint32_t interpolateDelay(uint32_t current, uint32_t total, uint32_t ramp, uint32_t minDelay, uint32_t maxDelay) {
    uint32_t half_length = total / 2;
    uint32_t x;
    if (current < half_length && current < ramp) {
        // Ramping up speed
        x = current;
    } else if ((current > ramp && current >= (total - ramp)) || (total - current) <= ramp) {
        // Ramp down speed
        x = total - current;
    } else {
        // Full speed
        return minDelay;
    }
    float a = (float(x) - float(ramp)) * (float(x) - float(ramp));
    auto b = float(ramp) * float(ramp);
    auto c = float(maxDelay) - float(minDelay);
    return static_cast<uint32_t>((a / (b / c)) + float(minDelay));
}

void MotorDriver::stepperTick(Stepper &stepper) {
    if (!stepper.isAtTarget()) {

        // Set up the interpolation functions
        uint32_t total = std::abs(stepper.target - stepper.targetStartStep);

        // Set the direction for the motor
        bool direction = stepper.step < stepper.target;
        stepper.dirPin.set(direction);

        // If the pulse counter has reached zero
        if (stepper.pulseMicrosecondCounter == 0) {

            // If the end of a high pulse, increment the step
            if (stepper.currentStepPinValue) {
                stepper.step += direction ? 1 : -1;
            }

            // Flip the stp pin
            stepper.stepPin.set(!stepper.currentStepPinValue);
            stepper.currentStepPinValue = !stepper.currentStepPinValue;

            // Reset the counter if we have not reached the target yet
            if (!stepper.isAtTarget()) {
                uint32_t current = std::abs(stepper.targetStartStep - stepper.step);
                stepper.pulseMicrosecondCounter = interpolateDelay(current, total, stepper.ramp, stepper.minDelay,
                                                                   stepper.maxDelay);
            }
        } else {
            stepper.pulseMicrosecondCounter--;
        }

    }
}
