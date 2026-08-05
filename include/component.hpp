#pragma once

#include <string>

struct ComponentDefinition {
    std::string name;
};

struct InitializeContext {
    // Context for runtime
};

class Component {
public:
    // Default destructor is defined as virtual for polymorphism so that if a pointer to a child class with type Component* is created, it will be properly destructed
    virtual ~Component() = default; 

    // const here ensures that 'this' (the Component instance) will not be altered in this call
    virtual ComponentDefinition definition() const = 0;
    
    // All others are also pure virtual functions so they need to be explicitly set in child classes, this also means Component class should not be instantiated directly
    virtual void initialize(const InitializeContext& context) = 0;
    virtual void reset() = 0;
    virtual void shutdown() = 0;
};

class FlightControl: public Component {
public:
    ComponentDefinition definition() const override;
    void initialize(const InitializeContext& context) override;
    void reset() override;
    void shutdown() override;
};
