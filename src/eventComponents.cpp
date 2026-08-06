#include "eventComponents.hpp"

#include <iostream>

void MissionCommandComponent::handleEvent(const EventContext& context, const Event& event) {
    switch (event.type) {
        case EventType::SetCommandedVelocity:
            state.commandedVelocity = event.value;
            break;
        case EventType::StopSimulation:
            break;
    }
}

void MissionCommandComponent::reset() {
    state.commandedVelocity = 0.0;
}

void ExternalForceComponent::handleEvent(const EventContext& context, const Event& event) {
    // Only handle external force command types
    if (event.type == EventType::SetExternalForce) {
        state.externalForce = event.value;
    }
}

void ExternalForceComponent::reset() {
    state.externalForce = 0.0;
}