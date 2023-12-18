#ifndef __PROGRAM_STATE_45C_HPP
#define __PROGRAM_STATE_45C_HPP

#include <vector>

class ProgramState
{

public:

	ProgramState();
	~ProgramState();

	size_t getCounter() const;

	// terminate means quit when something bad happened (e.g., trying to access a non-existent register)
	void terminate();

	// returns true if we're done running the program (and haven't crashed).
	bool done() const; 

	// Registers are numbered 0 .. NUM_REGISTERS - 1
	// eax is 0, ebx is 1, etc. 

	int getRegister(size_t registerNum) const;


// If you want to add additional public member functions, you may do so here.
// The above functions must remain with their given interface: 
//	the grading script expects it.
	void setRegister(size_t registerNum, int value);
	void setLessThanFlag(bool value);
	void setEqualToFlag(bool value);
	void setGreaterThanFlag(bool value);
	void setCounter(size_t value);
	void setProgramDone(bool value);
	bool getLessThanFlag();
	bool getEqualToFlag();
	bool getGreaterThanFlag();
	bool getProgramDone();

private:
// If you want to add private member variables, you may do so here.
	std::vector<int> registers;
	bool lessThanFlag{false};
	bool equalToFlag{false};
	bool greaterThanFlag{false};
	bool programDone;
	size_t counter;
};



#endif



