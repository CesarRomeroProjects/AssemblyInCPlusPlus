#include <vector>
#include <stdlib.h>
#include "ProgramState.hpp"


ProgramState::ProgramState()
{
	registers.resize(16);
}

ProgramState::~ProgramState() 
{}

size_t ProgramState::getCounter() const
{
	return counter;
}

void ProgramState::setCounter(size_t value)
{
	counter = value;
}

void ProgramState::terminate()
{
	exit(1); 
}


bool ProgramState::done() const
{
	return true;
}


int ProgramState::getRegister(size_t registerNum) const
{
	if (registerNum >= 0 && registerNum < 16)
		return registers.at(registerNum);
	else
		return 0;
}

void ProgramState::setRegister(size_t registerNum, int value)
{
	if (registerNum >= 0 && registerNum < 16)
		registers.at(registerNum) = value;
	else
		terminate();
}

void ProgramState::setLessThanFlag(bool value)
{
	lessThanFlag = value;
}

bool ProgramState::getLessThanFlag()
{
	return lessThanFlag;
}

void ProgramState::setEqualToFlag(bool value)
{
	equalToFlag = value;
}

bool ProgramState::getEqualToFlag()
{
	return equalToFlag;
}

void ProgramState::setGreaterThanFlag(bool value)
{
	greaterThanFlag = value;
}

bool ProgramState::getGreaterThanFlag()
{
	return greaterThanFlag;
}

void ProgramState::setProgramDone(bool value)
{
	programDone = value;
}

bool ProgramState::getProgramDone()
{
	return programDone;
}
