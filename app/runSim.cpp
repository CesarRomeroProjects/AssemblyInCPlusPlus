#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "runSim.hpp"
#include "ProgramState.hpp"

#include "Statement.hpp"
#include "MoveInstruction.hpp"
#include "AddInstruction.hpp"
#include "SubtractionInstruction.hpp"
#include "ImulInstruction.hpp"
#include "IncInstruction.hpp"
#include "CmpInstruction.hpp"
#include "JmpInstruction.hpp"
#include "JLInstruction.hpp"
#include "JEInstruction.hpp"
#include "EndInstruction.hpp"

// Simulates the given program.  The starting program state
// will be provided to you via the second parameter. 
// It is expected that you use this one, not a newly declared
// one, in running your program.
void runSimulator(std::istream &in, ProgramState * ps)
{
    // You will want to modify some of this.
    // You do not need to be very well versed in how std::stringstream works
    // You should be able to figure out how it works based on 
    // your knowledge of aspects like std::cin and reading the existing
    // code.  That is a skill worth developing!

    std::string line, word;
    std::string token1, token2;
    std::stringstream ss;
    std::vector<std::string> programLines;

    ps->setCounter(1);
    ps->setProgramDone(false);
    bool JMPLoop{false};
    bool JLLoop{false};
    bool JELoop{false};

    while ( getline(in, line) )
        programLines.push_back(line);

    while ( (ps->getCounter() - 1 < programLines.size()) && !ps->getProgramDone() ) 
    {
        ss.clear();
        ss.str( programLines[ps->getCounter() - 1] );
        while( ss >> word ) {
            // Instructs the MoveInstruction.
            if( "MOV" == word ) {
                ss >> token1 >> token2;
                Statement *m1 = new MoveInstruction(token1, token2);
                m1->execute(ps);
                delete m1;
            } 
            // Instructs the AddInstruction.
            else if ( "ADD" == word ) {
                ss >> token1 >> token2;
                Statement *m2 = new AddInstruction(token2, token1);
                m2->execute(ps);
                delete m2;
            } 
            // Instructs the SubstractionInstruction.
            else if ( "SUB" == word ) {
                ss >> token1 >> token2;
                Statement *m3 = new SubtractionInstruction(token2, token1);
                m3->execute(ps);
                delete m3;
            }
            // Instructs the ImulInstruction. 
            else if ( "IMUL" == word ) {
                ss >> token1 >> token2;
                Statement *m4 = new ImulInstruction(token2, token1);
                m4->execute(ps);
                delete m4;
            } 
            // Instructs the IncInstruction.
            else if ( "INC" == word ) {
                ss >> token1;
                Statement *m5 = new IncInstruction(token1);
                m5->execute(ps);
                delete m5;
            } 
            // Instructs the CmpInstruction.
            else if ( "CMP" == word ) {
                ss >> token1 >> token2;
                Statement *m6 = new CmpInstruction(token1, token2);
                m6->execute(ps);
                delete m6;
            } 
            // Instructs the JmpInstruction.
            else if ( "JMP" == word ) {
                // A conditional is used to check if we jumped backwards. (No infinite loop)
                if (!JMPLoop) {
                    size_t counterHolder{ps->getCounter()};
                    ss >> token1;
                    Statement *m7 = new JmpInstruction(token1);
                    m7->execute(ps);
                    delete m7;

                    // If jumped backwards, unconditionalJump is set to true to not cause an infinite loop.
                    if ( ps->getCounter() <= programLines.size() && ps->getCounter() < counterHolder && ps->getCounter() > 0 )
                        JMPLoop = true;
                    else if ( ps->getCounter() <= programLines.size() && ps->getCounter() > counterHolder && ps->getCounter() > 0 )
                        JMPLoop = false;
                    else
                        ps->setCounter(counterHolder);
                } 
                else {
                    ps->setProgramDone(true);
                    break;
                }
            } 
            // Instructs the JLInstruction.
            else if ( "JL" == word ) {
                // A conditional is used to check if we jumped backwards. (No infinite loop)
                if ( !JLLoop ) {
                    size_t counterHolder{ps->getCounter()};
                    ss >> token1;
                    Statement *m8 = new JLInstruction(token1);
                    m8->execute(ps);
                    delete m8;

                    // If jumped backwards, unconditionalJump is set to true to not cause an infinite loop.
                    if ( ps->getCounter() <= programLines.size() && ps->getCounter() < counterHolder && ps->getCounter() > 0 )
                        JLLoop = true;
                    else if ( ps->getCounter() <= programLines.size() && ps->getCounter() > counterHolder && ps->getCounter() > 0 )
                        JLLoop = false;
                    else
                        ps->setCounter(counterHolder);
                } 
                else {
                    ps->setProgramDone(true);
                    break;
                }
            } 
            
            // Instructs the JEInstruction.
            else if ( "JE" == word ) {
                // A conditional is used to check if we jumped backwards. (No infinite loop)
                if ( !JELoop ) {
                    size_t counterHolder{ps->getCounter()};
                    ss >> token1;
                    Statement *m9 = new JEInstruction(token1);
                    m9->execute(ps);
                    delete m9;

                    // If jumped backwards, unconditionalJump is set to true to not cause an infinite loop.
                    if ( ps->getCounter() <= programLines.size() && ps->getCounter() < counterHolder && ps->getCounter() > 0 )
                        JELoop = true;
                    else if ( ps->getCounter() <= programLines.size() && ps->getCounter() > counterHolder && ps->getCounter() > 0 )
                        JELoop = false;
                    else
                        ps->setCounter(counterHolder);
                } 
                else {
                    ps->setProgramDone(true);
                    break;
                }
            } 
            
            // Instructs the EndInstruction.
            else if ( "END" == word ) {
                Statement *m10 = new EndInstruction();
                m10->execute(ps);
                delete m10;
                break;
            }
            ps->setCounter(ps->getCounter() + 1);
        }
    }
}
