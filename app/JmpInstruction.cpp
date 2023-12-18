#include <string>
#include "JmpInstruction.hpp"


JmpInstruction::JmpInstruction(const std::string & dst)
    : destination(dst) {}

void JmpInstruction::execute(ProgramState * state) const
{
    state->setCounter(std::stoi(destination));
}
