#include <vector>
#include <functional>

#include "fixedComponents.hpp"
#include "eventComponents.hpp"
#include "continuousComponents.hpp"
#include "simulationRuntime.hpp"
#include "logger.hpp"

int main() {
    SimulationSignals state;

    FlightControlComponent flightControl(
        state,
        100.0,
        500.0
    );
    VehicleDynamicsComponent vehicleDynamics(state);
    MissionCommandComponent missionCommand(state);
    ExternalForceComponent externalForce(state);
    StateLogger stateLogger(state);

    std::vector<std::reference_wrapper<EventComponent>> eventComponents {
        missionCommand,
        externalForce
    };

    std::vector<Event> events{
        {
            .time = 1.0,
            .type = EventType::SetCommandedVelocity,
            .value = 10.0
        },
        {
            .time = 2.0,
            .type = EventType::SetExternalForce,
            .value = 500.0 // Newtons
        },
        {
            .time = 3.0,
            .type = EventType::SetCommandedVelocity,
            .value = 0.0
        },
        {
            .time = 4.0,
            .type = EventType::SetExternalForce,
            .value = -500.0 // Newtons
        }
    };

    SimulationRuntime runtime(
        flightControl,
        vehicleDynamics,
        eventComponents,
        stateLogger,
        events,
        5.0
    );

    runtime.run();
    return 0;
}