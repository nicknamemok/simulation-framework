#pragma once

struct ComponentDefinition {
    string name;
    vector<InputDefinition> inputs;
    vector<OutputDefinition> outputs;
};

struct FixedStepComponentDefinition {
    ComponentDefinition base;
    double period_s;
};

struct ContinuousStepComponentDefinition {
    ComponentDefinition base;
    double base_time;
};

struct EventComponentDefinition {
    ComponentDefinition base;
    bool something;
};

class Component {
public:
    virtual ComponentDefinition definition() const = 0;
    virtual void initialize(const InitializeContext& context) = 0;
    virtual ~Component() = default; 
};

class FixedStepComponent : public Component {
public:
    void definition(FixedStepComponentDefinition& component_definition) const override;
    void initialize(const InitializeContext& context);
};

class ContinuousStepComponent : public Component {
public:
    void definition(ContinuousStepComponentDefinition& component_definition) const override;
    void initialize(const InitializeContext& context);
};

class EventComponent : public Component {
public:
    definition(EventComponentDefinition& component_definition) const override;
    void initialize(const InitializeContext& context);
};
