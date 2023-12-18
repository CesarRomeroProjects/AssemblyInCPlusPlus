#include "catch_amalgamated.hpp"
#include "ProgramState.hpp"
#include "Statement.hpp"
#include "MoveInstruction.hpp"
#include "AddInstruction.hpp"
#include "SubtractionInstruction.hpp"
#include "ImulInstruction.hpp"
#include "CmpInstruction.hpp"
#include "JmpInstruction.hpp"
#include "JLInstruction.hpp"
#include "JEInstruction.hpp"
#include "EndInstruction.hpp"
#include "runSim.hpp"
#include <fstream>
#include <string>

// NOTE:  these are not intended as exhaustive tests.
// This should get you started testing.
// However, be aware that if ANY test marked "Required" fails, 
// your score for the portion will be zero, regardless of other considerations.


namespace{


/*
This LOOKS LIKE a lot of test cases!  
Remember you DO NOT need to pass every case the first time you build.
build and run tests for the starting code, and look through the case(s) that fail.
Read the description in the test files.

Decide which one you think will be the easiest to achieve:  what is the smallest amount of programming you can do to pass one more test case?  Write that code and find out.  If you now pass it, repeat -- what is the smallest amount of programming you can do to pass one more test case (without causing any previously-passing test cases to now fail).

Believe it or not, this will make programming a lot easier.  In future projects, you might want to write a lot of different test cases yourself at the beginning, based on reading the skeleton code and the project requirements, and then try the above approach.  You might find yourself turning what feels like a very large and intimidating programming assignment into a series of small, very manageable mini-projects. 

*/

TEST_CASE("StoreAConstant", "[RequiredMoveOperations]")
{
        ProgramState ps;
        MoveInstruction m1{"eax", "15"};
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);
}

TEST_CASE("MoveAConstant", "[RequiredMoveOperations]")
{
        ProgramState ps;
        MoveInstruction m1{"eax", "15"};
        m1.execute(&ps);
        MoveInstruction m2{"ebx", "eax"};
        m2.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);
        REQUIRE(ps.getRegister(1) == 15);
}

TEST_CASE("MoveUsesPolymorphism", "[RequiredMoveOperations]")
{
        ProgramState ps;
        Statement * m1 = new MoveInstruction{"eax", "15"};
        m1->execute(&ps);
        Statement * m2 = new MoveInstruction{"ebx", "eax"};
        m2->execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);
        REQUIRE(ps.getRegister(1) == 15);

        delete m1;
        delete m2;
}

TEST_CASE("AddAConstant", "[RequiredArithmeticOperations]")
{
        ProgramState ps;
        MoveInstruction m1("eax", "15");
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);

        AddInstruction ai1("eax", "20");
        ai1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 35);
}

TEST_CASE("AddARegister", "[RequiredArithmeticOperations]")
{
        ProgramState ps;
        MoveInstruction m1("eax", "15");
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);

        MoveInstruction m2("ebx", "20");
        m2.execute(&ps);
        REQUIRE(ps.getRegister(1) == 20);

        AddInstruction ai1("eax", "ebx");
        ai1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 35);
}

// This test case is NOT REQUIRED to be eligible for grading.
// Remember that does not mean that this functionality won't
// be graded;  rather, it just means this test does not affect
// your eligibility to be graded.
// This is provided to demonstrate functionality of the subtract operation.
TEST_CASE("Subtraction", "[FYI]")
{
        ProgramState ps;
        MoveInstruction m1{"eax", "15"};
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15);

        MoveInstruction m2{"ebx", "20"};
        m2.execute(&ps);
        REQUIRE(ps.getRegister(1) == 20);

        SubtractionInstruction si1{"eax", "ebx"};
        si1.execute(&ps);
        REQUIRE(ps.getRegister(0) == -5);
}

// [RequiredAllOperations] does an unconditional jump and the program counter changes appropriately. 

TEST_CASE("UnconditionalJump", "[RequiredAllOperations]")
{
        ProgramState ps;
        JmpInstruction js{"5"};
        js.execute(&ps);
        REQUIRE(ps.getCounter() == 5);
}

// "Full Programs" test cases use the full set of available operations,
// although some individual programs may only use a subset.

TEST_CASE("StoreAConstantAsAProgram", "[RequiredFullPrograms]")
{
        std::ifstream in{"prog1.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 15);
        REQUIRE(ps.getRegister(1) == 20);
}

TEST_CASE("MoveAConstantAsAProgram", "[RequiredFullPrograms]")
{
        std::ifstream in{"prog2.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 15);
        REQUIRE(ps.getRegister(1) == 15);
}

TEST_CASE("FullProgramTest1", "[FYI]")
{
        std::ifstream in {"prog3.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 20);
        REQUIRE(ps.getRegister(1) == 0);
        REQUIRE(ps.getRegister(2) == -40);
        REQUIRE(ps.getRegister(15) == 20);

        for (size_t i{3}; i < 15; i++)
                REQUIRE(ps.getRegister(i) == 0);

        REQUIRE(ps.getCounter() == 6);
}

TEST_CASE("FullProgramTest2", "[FYI]")
{
        std::ifstream in {"prog4.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(15) == 1);

        for (size_t i{0}; i < 15; i++)
                REQUIRE(ps.getRegister(i) == 0);
        
        REQUIRE(ps.getCounter() == 6);
}

TEST_CASE("FullProgramTest3", "[FYI]")
{
        std::ifstream in {"prog5.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 10);
        REQUIRE(ps.getRegister(1) == 20);
        REQUIRE(ps.getRegister(2) == 30);
        REQUIRE(ps.getCounter() == 5);
}

TEST_CASE("FullProgramTest4", "[FYI]")
{
        std::ifstream in {"prog6.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 10);
        REQUIRE(ps.getRegister(1) == 10);
        REQUIRE(ps.getRegister(2) == 10);
        REQUIRE(ps.getRegister(3) == 10);
        REQUIRE(ps.getRegister(4) == 15);
        REQUIRE(ps.getRegister(5) == 15);
        REQUIRE(ps.getRegister(6) == 15);
        REQUIRE(ps.getRegister(7) == 15);
        REQUIRE(ps.getLessThanFlag());
        REQUIRE(ps.getGreaterThanFlag() == false);
        REQUIRE(ps.getEqualToFlag() == false);
        REQUIRE(ps.getCounter() == 12);      
}

TEST_CASE("FullProgramTest5", "[FYI]")
{
        std::ifstream in {"prog7.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 10);
        REQUIRE(ps.getRegister(1) == 15);
        REQUIRE(ps.getRegister(2) == 20);
        REQUIRE(ps.getRegister(3) == 25);
        REQUIRE(ps.getRegister(4) == 10);
        REQUIRE(ps.getRegister(5) == 10);
        REQUIRE(ps.getRegister(6) == -10);
        REQUIRE(ps.getProgramDone());
        REQUIRE(ps.getCounter() == 9); 
} 

TEST_CASE("FullProgramTest6", "[FYI]")
{
        std::ifstream in {"prog8.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 12);
        REQUIRE(ps.getRegister(1) == 20);
        REQUIRE(ps.getLessThanFlag());
        REQUIRE(ps.getProgramDone());
        REQUIRE(ps.getCounter() == 9);
}

TEST_CASE("FullProgramTest7", "[FYI]")
{
        std::ifstream in {"prog9.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 80);
        REQUIRE(ps.getRegister(1) == 30);
        REQUIRE(ps.getRegister(2) == 10);
        REQUIRE(ps.getRegister(3) == 20);
        REQUIRE(ps.getRegister(4) == 20);
        REQUIRE(ps.getRegister(5) == 20);
        REQUIRE(ps.getRegister(6) == 20);
        REQUIRE(ps.getCounter() == 14);
}

TEST_CASE("FullProgramTest8", "[FYI]")
{
        std::ifstream in {"prog10.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 10);
        REQUIRE(ps.getRegister(1) == 20);
        REQUIRE(ps.getRegister(2) == 30);
        REQUIRE(ps.getCounter() == 5);
}

TEST_CASE("FullProgramTest9", "[FYI]")
{
        std::ifstream in {"prog11.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 10);
        REQUIRE(ps.getRegister(1) == 20);
        REQUIRE(ps.getRegister(2) == 30);
        REQUIRE(ps.getCounter() == 4);
}

TEST_CASE("FullProgramTest10", "[FYI]")
{
        std::ifstream in {"prog12.txt"};
        ProgramState ps;
        runSimulator(in, &ps);
        REQUIRE(ps.getRegister(0) == 10);
        REQUIRE(ps.getRegister(1) == 20);
        REQUIRE(ps.getRegister(2) == 30);
        REQUIRE(ps.getCounter() == 5);
}


TEST_CASE("Multiplication", "[FYI]")
{
        ProgramState ps;
        MoveInstruction m1{"eax", "15"};
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 15); 

        MoveInstruction m2{"ebx", "2"};
        m2.execute(&ps);
        REQUIRE(ps.getRegister(1) == 2);

        ImulInstruction ml1{"ebx", "eax"};
        ml1.execute(&ps);
        REQUIRE(ps.getRegister(1) == 30);

        ImulInstruction ml2{"ecx", "0"};
        ml2.execute(&ps);
        REQUIRE(ps.getRegister(2) == 0);

        ImulInstruction ml3{"eax", "3"};
        ml3.execute(&ps);
        REQUIRE(ps.getRegister(0) == 45);
}

TEST_CASE("JEPasses", "[FYI]")
{
        ProgramState ps;
        MoveInstruction m1{"eax", "20"};
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 20);

        AddInstruction a1{"ebx", "100000"};
        a1.execute(&ps);
        REQUIRE(ps.getRegister(1) == 100000);

        CmpInstruction c1{"eax", "ebx"};
        c1.execute(&ps);
        REQUIRE(ps.getLessThanFlag());
        REQUIRE(ps.getGreaterThanFlag() == false);
        REQUIRE(ps.getEqualToFlag() == false);

        JLInstruction jl1{"1"};
        jl1.execute(&ps);
        REQUIRE(ps.getCounter() == 1);
}

TEST_CASE("JEFails", "[FYI]")
{
        ProgramState ps;
        MoveInstruction m1{"eax", "20"};
        m1.execute(&ps);
        REQUIRE(ps.getRegister(0) == 20);

        AddInstruction a1{"ebx", "100000"};
        a1.execute(&ps);
        REQUIRE(ps.getRegister(1) == 100000);

        CmpInstruction c1{"ebx", "eax"};
        c1.execute(&ps);
        REQUIRE(ps.getLessThanFlag() == false);
        REQUIRE(ps.getGreaterThanFlag() == true);
        REQUIRE(ps.getEqualToFlag() == false);

        JLInstruction jl1{"1"};
        jl1.execute(&ps);
        REQUIRE(ps.getCounter() == 0);
}

} // end namespace

