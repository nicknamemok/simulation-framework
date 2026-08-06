#include "logger.hpp"

#include <iostream>

void StateLogger::step(const FixedStepContext& context) {
    std::cout << "########### Current State ###########" << std::endl
    << "Timestamp: " << context.currentTime << std::endl
    << "PositionX: " << state.positionX << std::endl
    << "VelocityX: " << state.velocityX << std::endl
    << "Commanded Velocity: " << state.commandedVelocity << std::endl
    << "Control Force: " << state.controlForce << std::endl
    << "#####################################" << std::endl << std::endl;
};

// Reseting logger does nothing for now
void StateLogger::reset() {};