#include <string>
#include "CmpInstruction.hpp"


CmpInstruction::CmpInstruction(const std::string & lhs, const std::string & rhs)
    : m_lhs(lhs), m_rhs(rhs) {}

void CmpInstruction::execute(ProgramState * state) const
{
    int lhsValue{0};
    int rhsValue{0};

    // Dealing with the first parameter.
    if ( m_lhs.find_first_not_of("abcdefghijklmnopx") == std::string::npos ) 
    {
        if ( m_lhs.size() == 3 && ( m_lhs.at(0) != 'e' || m_lhs.at(2) != 'x' ) )
            state->terminate();

        int registerNumber{static_cast<int>(m_lhs.at(1)) - 97};
        lhsValue = state->getRegister(registerNumber);
    }
    else if ( m_lhs.find_first_not_of("-0123456789") == std::string::npos ) 
    {
        if ( m_lhs.size() == 1 && m_lhs.at(0) == '-' )
            state->terminate();
        
        lhsValue = std::stoi(m_lhs);
    } 
    else
        state->terminate();


    // Dealing with the second parameter.
    if ( m_rhs.find_first_not_of("abcdefghijklmnopx") == std::string::npos ) 
    {
        if ( m_rhs.size() == 3 && ( m_rhs.at(0) != 'e' || m_rhs.at(2) != 'x' ) )
            state->terminate();

        int registerNumber{static_cast<int>(m_rhs.at(1)) - 97};
        rhsValue = state->getRegister(registerNumber);
    }
    else if ( m_rhs.find_first_not_of("-0123456789") == std::string::npos ) 
    {
        if ( m_rhs.size() == 1 && m_rhs.at(0) == '-' )
            state->terminate();
        
        rhsValue = std::stoi(m_rhs);
    } 
    else
        state->terminate();


    if (lhsValue < rhsValue) {
        state->setLessThanFlag(true);
        state->setEqualToFlag(false);
        state->setGreaterThanFlag(false);
    } else if (lhsValue == rhsValue) {
        state->setLessThanFlag(false);
        state->setEqualToFlag(true);
        state->setGreaterThanFlag(false);
    } else {
        state->setLessThanFlag(false);
        state->setEqualToFlag(false);
        state->setGreaterThanFlag(true);
    }
}
