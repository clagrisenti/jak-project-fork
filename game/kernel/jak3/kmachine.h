#include <string>
#include <vector>

#pragma once

namespace jak3 {
void InitParms(int argc, const std::vector<std::string>& argv);
void InitMachineScheme();
int InitMachine();
int ShutdownMachine();
}  // namespace jak3
