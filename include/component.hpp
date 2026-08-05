#pragma once

#include <string>

struct ComponentDefinition {
    std::string name;
};

struct InitializeContext {
    // Context for runtime
};

struct SimulationSignals {
    // Inputs
    double commandedVelocity = 0.0;
    double controlForce = 0.0;

    // States
    double positionX = 0.0;
    double velocityX = 0.0;
};

class Component {
protected:
    SimulationSignals& state;

public:
    explicit Component(SimulationSignals& _state) : state(_state) {}

    // Default destructor is defined as virtual for polymorphism so that if a pointer to a child class with type Component* is created, it will be properly destructed
    virtual ~Component() = default; 
    
    // All others are also pure virtual functions so they need to be explicitly set in child classes, this also means Component class should not be instantiated directly
    // const here ensures that 'this' (the Component instance) will not be altered in this call
    // virtual ComponentDefinition definition() const = 0;
    virtual void reset() = 0;
};
