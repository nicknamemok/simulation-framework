#pragma once

#include "fixedComponents.hpp"

class StateLogger : public FixedStepComponent {
public:
    explicit StateLogger(SimulationSignals& _state, double _loggingFrequencyS = 1.0)
    : FixedStepComponent(1/_loggingFrequencyS, _state) {};

    void step(const FixedStepContext& context) override;
    void reset() override;
};