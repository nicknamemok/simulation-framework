#include <algorithm>
#include <utility>

#include "simulationRuntime.hpp"
#include "continuousComponents.hpp"
#include "fixedComponents.hpp"

SimulationRuntime::run() {
    // Initial reset
    flightControlComponent.reset();
    vehicleDynamicsComponent.reset();
    missionCommandComponent.reset();

    const double controllerPeriod = 1 / flightControlComponent.getFreqHz();
    // Initialize 0.0 controller time as we need to initialize the initial state
    double nextControllerTime = 0.0;

    while (currentTime < endTime) {
        // That way if we're a the end of our events, we take endTime as the next event
        double nextEventTime = endTime;

        // Get the time of the next event
        if (nextEventIdx < events.size()) {
            nextEventTime = events[nextEventIdx].time;
        }

        // We then step our simulation up to the minimum of:
        // next event, next fixed time step move, and end time
        const double nextTime = std::min(
            nextControllerTime,
            nextEventTime,
            endTime
        );

        // Internally advance the vehicle dynamics (continuous component) up until that point
        vehicleDynamicsComponent.advance(
            ContinuousContext{
                .startTime = currentTime,
                .endTime = endTime
            }
        );
        currentTime = nextTime;

        // After which we process all events up to that point in time, the reason is that there might be many events at that time
        while (
            nextEventIdx < events.size() &&
            events[nextEventIdx].time <= currentTime
        ) {
            missionCommandComponent.handleEvent(
                events[nextEventIdx],
                EventsContext{
                    .currentTime = currentTime
                }
            );
            nextEventIdx++;
        }

        // Then we handle any controller events up to that point in time, we don't need to do a while loop because it can only advance at most once due to the min above
        if (nextControllerTime <= currentTime) {
            flightControlComponent.step(
                FixedStepContext{
                    .currentTime = currentTime,
                    .deltaTime = controllerPeriod
                }
            );
            // We only advance the controller time if we've actually processed a command, if not we keep it and see if we need to advance it the next loop
            nextControllerTime += controllerPeriod;
        }

        // End sim
        if (currentTime >= endTime) {
            break;
        }
    }
}