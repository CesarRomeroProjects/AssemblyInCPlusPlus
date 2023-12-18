#include <string>
#include "IncInstruction.hpp"


IncInstruction::IncInstruction(const std::string & reg)
    : m_register(reg) {}

void IncInstruction::execute(ProgramState * state) const
{
    if ( m_register.find_first_not_of("abcdefghijklmnopx") == std::string::npos ) {
        // Program's terminated because of invalid formatting for accessing register(s).
        if ( m_register.size() == 3 && (m_register.at(0) != 'e' || m_register.at(2) != 'x') ) 
            state->terminate();

        int destRegisterNumber{static_cast<int>(m_register.at(1)) - 97}; // Declaring the register that is going to be accessed.
        int destRegisterValue = state->getRegister(destRegisterNumber) + 1;
        state->setRegister(destRegisterNumber, destRegisterValue);
    }
}