#include <string>
#include "JLInstruction.hpp"


JLInstruction::JLInstruction(const std::string & dst)
    : lineDestination(dst) {}

void JLInstruction::execute(ProgramState * state) const
{
    if ( state->getLessThanFlag() )
        state->setCounter(std::stoi(lineDestination));
}
