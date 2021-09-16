#pragma once
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <fstream>
#include <stringUtils.h>


typedef std::vector< std::string> ListOfStrings;
typedef std::map<std::string, uint16_t> DirectiveToNumber;
typedef std::map<std::string, std::string> OpCodeToInstruction;

typedef std::tuple<
    uint16_t, 
    std::string,
    std::string,
    std::string
> AddressOpcodeArgsLine;


// map<[PC] [PC, opcode, arg1, arg2]>
// address opcode/value arg1 arg2 lineOriginalFile 
typedef std::map<uint16_t, AddressOpcodeArgsLine > FileLines;

class Simulator {
    public:
        Simulator(std::string fileName);
        ~Simulator();
        void simulate();

    private:
        uint16_t PC = 0;
        uint16_t ACC = 0;
        uint16_t MEM = 0;
        bool reachedSTOP = false;
        
        OpCodeToInstruction opcodeToInstruction = {
            {"0", "SPACE"},
            {"1", "ADD"},
            {"2", "SUB"},
            {"3", "MULT"},
            {"4", "DIV"},
            {"5", "JMP"},
            {"6", "JMPN"},
            {"7", "JMPP"},
            {"8", "JMPZ"},
            {"9", "COPY"},
            {"10", "LOAD"},
            {"11", "STORE"},
            {"12", "INPUT"},
            {"13", "OUTPUT"},
            {"14", "STOP"},
            {"15", "NULL"}
        };
        DirectiveToNumber instructToSizeInMemory = { // shows Number of arguments valueMap.second-1 
            {"ADD", 2},
            {"SUB", 2},
            {"MULT", 2},
            {"DIV", 2},
            {"JMP", 2},
            {"JMPN", 2},
            {"JMPP", 2},
            {"JMPZ", 2},
            {"COPY", 3},
            {"LOAD", 2},
            {"STORE", 2},
            {"INPUT", 2},
            {"OUTPUT", 2},
            {"STOP", 1},
            {"SPACE", 1},
            {"CONST", 1}
        };  

        std::string fileContentsStrint;
        ListOfStrings fileContents;
        FileLines fileLines;

        std::string fileName;
        std::string fileDir;
        std::fstream input;
        void setFileContents();
        void setFileLines();
        void printFileLines();
        void printTuple(
            uint16_t pc,
            std::string instruction,
            std::string arg1,
            std::string arg2
        );
        
        void execute();


};

#endif