#pragma once
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <fstream>
#include <iostream>
#include <map>
#include <symboltable.h>

typedef std::vector< std::string> ListOfStrings;
typedef std::vector< std::tuple<uint16_t, std::vector< std::string>> > FileLines;

class Assembler {
    public:
        Assembler(std::fstream *source, std::string fileName);
        ~Assembler();
        void assembleFile();
    private:

        const std::map<std::string, uint8_t> instructionToOpcode = {
            {"SPACE", 0},
            {"ADD", 1},
            {"SUB", 2},
            {"MULT", 3},
            {"DIV", 4},
            {"JMP", 5},
            {"JMPN", 6},
            {"JMPP", 7},
            {"JMPZ", 8},
            {"COPY", 9},
            {"LOAD", 10},
            {"STORE", 11},
            {"INPUT", 12},
            {"OUTPUT", 13},
            {"STOP", 14}
        };
        const std::map<std::string, uint8_t> instructionToSizeInMemory = {
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
        };  
            const std::map<std::string, uint8_t> dataToSizeInMemory = {
            {"CONST", 1},
            {"SPACE", 1}, // TODO: CHANGE THIS
        };  

        SymbolTable symbolTable;

        std::fstream * sourceCode;
        std::fstream * assemblingCode;
        std::fstream * assembledCode;

        std::string fileName = "binComments.asm";
        
        void onePassAlgorithm();
        bool isEOF();
        bool isComment();
        void writeAssembledFile();
        
        // TOKEN
        std::string readToken();
        std::string readUntilEndToken(); 
        bool isInstruction(std::string token);
        std::string getOpCode(std::string token);
        bool isValidLabel(std::string token);
        bool isDefinition(std::string token);
        // END TOKEN

        void updatesAllUsedPositions();
        void updatesAssembledCodeAtPosition(uint16_t position, uint16_t addressValue);
        ListOfStrings getUsedPositionsOfLabel(std::string label);
        void addsToUsedPosition(std::string label, uint16_t address);
        void readTillNextSectionOrEOF();

};

#endif