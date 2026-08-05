#pragma once

#include <string>
#include "./component.hpp"

struct FixedStepContext {
    double currentTime;
    double deltaTime;
};

class FixedStepComponent: public Component {
private:
    const double freqHz;

public:
    // Constructor. List initializer is preferred and should be default in constructors as they always work while assignment sometimes doesn't work
    // explicit is used so that there will be no implicit interpretation of inputs
    explicit FixedStepComponent(double _freqHz, SimulationSignals& _state) : freqHz(_freqHz), Component(_state) {}

    // Getter function
    double getfreqHz();

    // const guarantees we don't change context even when we're passing by reference, and full virtual means abstract function
    virtual void step(const FixedStepContext& context) = 0;
};

class FlightControlComponent: public FixedStepComponent {
private:
    const double gain;
    const std::string componentName = "FlightController";

public:
    // state is a reference so once we pass it in within the constructor, we have access to the latest values
    // but need to be careful since it is not a const so we can alter it, need to make sure causality is not violated.
    // reference also needs to be list initialized.
    explicit FlightControlComponent(SimulationSignals& _state, double _freqHz = 100, double _gain = 500.0)
    : FixedStepComponent(_freqHz, _state), gain(_gain) {}

    // Simple flight controller step function that calculates the difference in velocity and compuets a control force based on a delta and gain
    void step(const FixedStepContext& context) override;

    void reset() override;
}