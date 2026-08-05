#include "fixedComponents.hpp"

double FixedStepComponent::getfreqHz() {
    return freqHz;
}

void FlightControlComponent::step(const FixedStepContext& context) {
    double delta = state.commandedVelocity - state.velocityX;
    state.controlForce = delta * gain;
}

void FlightControlComponent::reset() {
    state.controlForce = 0;
}