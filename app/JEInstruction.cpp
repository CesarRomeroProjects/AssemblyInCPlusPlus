#include <string>
#include "JEInstruction.hpp"


JEInstruction::JEInstruction(const std::string & dst)
    : lineDestination(dst) {}

void JEInstruction::execute(ProgramState * state) const
{
    if ( state->getEqualToFlag() )
        state->setCounter(std::stoi(lineDestination));
}

