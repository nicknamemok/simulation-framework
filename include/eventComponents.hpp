#pragma once

#include "./component.hpp"

enum struct EventType {
    SetCommandedVelocity,
    StopSimulation
}

struct EventContext {
    double currentTime;
}

struct Event {
    double time;
    EventType type;
    double value = 0.0;
}

class EventComponent : public Component {
public:
    explict EventComponent(SimulationSignals& _state)
    : Component(_state) {}

    virtual void handleEvent(const EventContext& context, const Event& event) = 0;
}

class MissionCommandComponent : public EventCommand {
public:
    explict MissionCommandComponent(SimulationSignals& _state)
    : EventComponent(_state)

    void handleEvent(const EventContext& context, const Event& event) override;
    void reset() override;
}
