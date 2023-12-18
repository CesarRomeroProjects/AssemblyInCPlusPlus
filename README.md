# Project 3: Assembly in C++

# Overview
This project involves interpreting a simplified version of executable code in the x86-45c architecture. You will implement a simulator for an instruction set architecture, including registers, arithmetic operations, and conditional jumps.

# Instruction Set Architecture
The x86-45c architecture is designed for a computer chip with unique characteristics. It uses registers instead of declared variables and has condition code registers to remember the result of the last comparison. Instructions are written in all capital letters, and registers are in lowercase letters.

# Instructions
The instruction set includes move (MOV), arithmetic operations (ADD, SUB, IMUL, INC), comparison (CMP), and jump instructions (JMP, JL, JE). The program state is defined by the program's running status, the next line of code to execute, and the values of the sixteen registers.

# The Simulator
The assignment involves writing a simulator for x86-45c assembly. The ProgramState class plays a crucial role, and you will need to extend its public interface, add private member variables, and define functions. Additionally, you'll work on the terminate() function for program termination.

# Implementation Notes
- The terminate() function is for emergency termination and will not be used in testing.
- You need to implement code in the runSim.cpp file, especially the input reading function.

# Restrictions
- Avoid using libraries not covered in lectures.
- You are encouraged to add helper functions, both private and public, but do not remove or change declared functions.
- Inheritance and polymorphism must be used appropriately for all program instructions.