#include <vector>

#include "./fixedComponents.hpp"
#include "./eventComponents.hpp"
#include "./continuousComponents"
#include "./simulationRuntime.hpp"

int main() {
    SimulationSignals state;

    FlightControlComponent flightControl(
        state,
        100.0,
        500.0
    );
    VehicleDynamicsComponent vehicleDynamics(state);
    MissionCommandComponent missionCommand(state);

    std::vector<Event> events{
        {
            .time = 1.0,
            .type = EventType::SetCommandedVelocity,
            .value = 10.0
        },
        {
            .time = 3.0,
            .type = EventType::SetCommandedVelocity,
            .value = 0.0
        }
    };

    SimulationRuntime runtime(
        flightControl,
        vehicleDynamics,
        missionCommand,
        events,
        5.0
    );

    runtime.run();
    return 0;
}