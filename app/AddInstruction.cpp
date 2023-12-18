#include <string>
#include "AddInstruction.hpp"


AddInstruction::AddInstruction(const std::string & dest, const std::string & src)
    : destination(dest), source(src) {}

void AddInstruction::execute(ProgramState * state) const
{
    int registerValue{0};

    if (destination.find_first_not_of("abcdefghijklmnopx") == std::string::npos) 
    {
        // Program's terminated because of invalid formatting for accessing register(s).
        if ( destination.size() == 3 && (destination.at(0) != 'e' || destination.at(2) != 'x') ) 
            state->terminate();

        int destRegisterNumber{static_cast<int>(destination.at(1)) - 97};
        int destRegisterValue = state->getRegister(destRegisterNumber);

        if (source.find_first_not_of("abcdefghijklmnopx") == std::string::npos) 
        { 
            // Program's terminated because of invalid formatting for accessing register(s).
            if (source.size() == 3 && (source.at(0) != 'e' || source.at(2) != 'x') )
                state->terminate();

            int srcRegisterNumber = static_cast<int>(source.at(1)) - 97; 
            registerValue = destRegisterValue + state->getRegister(srcRegisterNumber);
        } 
        else if (source.find_first_not_of("-0123456789") == std::string::npos) 
        {
            // Program's terminated because the input for the source is only '-'.
            if (source.size() == 1 && source.at(0) == '-')
                state->terminate();

            registerValue = destRegisterValue + std::stoi(source);
        } 
        else 
            state->terminate();

        // This should set the destination register to its assigned value.
        state->setRegister(destRegisterNumber, registerValue);
    } 
    else 
        state->terminate();
}