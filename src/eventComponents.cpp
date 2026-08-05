#include "eventComponents.cpp"

void MissionCommandComponent::handleEvent(const EventContext& context, const Event& event) {
    switch (event.type) {
        case EventType::SetCommandedVelocity:
            state.commandedVelocity = event.value
            break;
        case EventType::StopSimulation:
            break;
    }
}

void MissionCommandComponent::reset() {
    state.commandedVelocity = 0.0;
}