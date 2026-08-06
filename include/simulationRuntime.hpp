#pragma once

#include <vector>
#include <functional>

#include "eventComponents.hpp"
#include "continuousComponents.hpp"
#include "fixedComponents.hpp"
#include "logger.hpp"

class SimulationRuntime {
private:
    FlightControlComponent& flightControlComponent;
    VehicleDynamicsComponent& vehicleDynamicsComponent;
    std::vector<std::reference_wrapper<EventComponent>> eventComponents;
    StateLogger& stateLoggerComponent;
    std::vector<Event>& events;
    
    double currentTime = 0.0;
    double endTime;

    std::size_t nextEventIdx = 0;

public:
    SimulationRuntime(
        FlightControlComponent& _flightControlComponent,
        VehicleDynamicsComponent& _vehicleDynamicsComponent,
        std::vector<std::reference_wrapper<EventComponent>>& _eventComponents,
        StateLogger& _stateLoggerComponent,
        std::vector<Event>& _events,
        double _endTime
    )
    : flightControlComponent(_flightControlComponent),
      vehicleDynamicsComponent(_vehicleDynamicsComponent),
      eventComponents(_eventComponents),
      stateLoggerComponent(_stateLoggerComponent),
      events(_events),
      endTime(_endTime) {}

    void run();
};