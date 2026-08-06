#pragma once

#include "component.hpp"

enum struct EventType {
    SetCommandedVelocity,
    SetExternalForce,
    StopSimulation
};

struct EventContext {
    double currentTime;
};

struct Event {
    double time;
    EventType type;
    double value = 0.0;
};

class EventComponent : public Component {
public:
    explicit EventComponent(SimulationSignals& _state)
    : Component(_state) {};

    virtual void handleEvent(const EventContext& context, const Event& event) = 0;
};

class MissionCommandComponent : public EventComponent {
public:
    explicit MissionCommandComponent(SimulationSignals& _state)
    : EventComponent(_state) {};

    void handleEvent(const EventContext& context, const Event& event) override;
    void reset() override;
};

class ExternalForceComponent : public EventComponent {
public:
    explicit ExternalForceComponent(SimulationSignals& _state)
    : EventComponent(_state) {};

    void handleEvent(const EventContext& context, const Event& event) override;
    void reset() override;
};
