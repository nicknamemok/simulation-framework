#include <algorithm>
#include <utility>

#include "simulationRuntime.hpp"
#include "continuousComponents.hpp"
#include "fixedComponents.hpp"

void SimulationRuntime::run() {
    // Initial reset
    flightControlComponent.reset();
    vehicleDynamicsComponent.reset();
    // Reset all event components
    for (auto& component : eventComponents) {
        component.get().reset();
    }

    const double controllerPeriod = 1 / flightControlComponent.getFreqHz();
    const double loggerPeriod = 1 / stateLoggerComponent.getFreqHz();
    // Initialize 0.0 controller time as we need to initialize the initial state
    double nextControllerTime = 0.0;
    double nextLoggerTime = 0.0;

    while (currentTime < endTime) {
        // That way if we're a the end of our events, we take endTime as the next event
        double nextEventTime = endTime;

        // Get the time of the next event
        if (nextEventIdx < events.size()) {
            nextEventTime = events[nextEventIdx].time;
        }

        // We then step our simulation up to the minimum of:
        // next event, next fixed time step move, and end time
        const double nextTime = std::min({
            nextControllerTime,
            nextLoggerTime,
            nextEventTime,
            endTime
    });

        // Internally advance the vehicle dynamics (continuous component) up until that point
        vehicleDynamicsComponent.advance(
            ContinuousContext{
                .startTime = currentTime,
                .endTime = nextTime
            }
        );
        currentTime = nextTime;

        // Process events
        while (
            nextEventIdx < events.size() &&
            events[nextEventIdx].time <= currentTime
        ) {
            for (auto& component : eventComponents) {
                component.get().handleEvent(
                    EventContext{
                        .currentTime = currentTime
                    },
                    events[nextEventIdx]
                );
            }
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

        // Controller then logger
        if (nextLoggerTime <= currentTime) {
            stateLoggerComponent.step(
                FixedStepContext{
                    .currentTime = currentTime,
                    .deltaTime = loggerPeriod
                }
            );
            nextLoggerTime += loggerPeriod;
        }

        // End sim
        if (currentTime >= endTime) {
            break;
        }
    }
}