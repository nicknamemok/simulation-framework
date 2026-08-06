#pragma once

#include "./component.hpp"

struct ContinuousContext {
    double startTime;
    double endTime;
};

class ContinuousComponent : public Component {
private:
    double maxStepS;

public:
    explicit ContinuousComponent(SimulationSignals& _state, double _maxStepS)
    : Component(_state), maxStepS(_maxStepS) {}

    double getMaxStepS();

    // Abstract class
    virtual void advance(const ContinuousContext& context) = 0;
};

class VehicleDynamicsComponent : public ContinuousComponent {
private:
    const double mass;
    const double dragCoefficient;

public:
    VehicleDynamicsComponent(
        SimulationSignals& _state,
        double _maxStepS = 0.005,
        double _mass = 1000.0,
        double _dragCoefficient = 0.5
    ) : ContinuousComponent(_state, _maxStepS), mass(_mass), dragCoefficient(_dragCoefficient) {}

    void advance(const ContinuousContext& context) override;

    void reset() override;
};