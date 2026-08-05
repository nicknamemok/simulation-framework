#include "continuousComponents.hpp"

#include <algoirthm>

double ContinousComponent::getMaxStepS() {
    return maxStepS;
}

void VehicleDynamicsComponent::advance(const ContinuousContext& context) {
    // Time that we have resolved the EOM up until
    double integrationTime = context.startTime;

    while (integrationTime < context.endTime) {
        const double remainingTime = context.endTime - integrationTime;

        // The delta time is either the next event time (remaining time) or the max time we can go without an event
        // For this simple solver, we are internally time marching in this continuous component until the
        // last step which may be a partial step to the next even
        const deltaTime = std::min(
            getMaxStepS(),
            remainingTime
        )

        // Simple kinematics
        const acceleration = (
            state.controlForce -
            dragCoefficient * state.velocityX
        ) / mass;
        state.positionX += state.velocityX * deltaTime;
        state.velocityX += acceleration * deltaTime;

        integrationTime += deltaTime;
    }
}

void VehicleDynamicsComponent::reset() {
    state.positionX = 0.0;
    state.velocityX = 0.0;
}