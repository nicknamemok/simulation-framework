#pragma once

#include <vector>
#include

#include "./eventComponents"
#include "./continousComponents"
#include "./fixedComponents"

class SimulationRuntime {
private:
    FlightControlComponent& flightControlComponent;
    VehicleDynamicsComponent& vehicleDynamicsComponent;
    MissionCommandComponent& missionCommandComponent
    std::vector<Events>& events,
    
    double currentTime = 0.0;
    double endTime

    std::size_t nextEventIdx = 0;

public:
    SimulationRuntime(
        FlightControlComponent& _flightControlComponent,
        VehicleDynamicsComponent& _vehicleDynamicsComponent,
        MissionCommandComponent& _missionCommandComponent,
        std::vector<Events>& _events,
        double _endTime
    )
    : flightControlComponent(_flightControlComponent),
      vehicleDynamicsComponent(_vehicleDynamicsComponent),
      missionCommandComponent(_missionCommandComponent),
      events(_events),
      endTime(_endTime) {}

    void run();
}