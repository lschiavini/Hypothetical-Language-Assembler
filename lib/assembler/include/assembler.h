#pragma once
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <fstream>
#include <iostream>
#include <map>
#include <symboltable.h>

typedef std::vector< std::string> ListOfStrings;
typedef std::map<std::string, uint16_t> DirectiveToNumber;

// address opcode/value arg1 arg2 lineOriginalFile 
typedef std::tuple< std::string, std::string, std::string, uint16_t > OpcodeArgsLine;
typedef std::map<std::string, OpcodeArgsLine > FileLines;

class Assembler {
    public:
        Assembler(std::fstream *source, std::string fileName);
        ~Assembler();
        void assembleFile();
    private:
        DirectiveToNumber instructionToOpcode = {
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
            {"CONST", 1}, // TODO: CHANGE THIS
        };  
        DirectiveToNumber dataToSizeInMemory = {
        };  


        SymbolTable symbolTable;
        FileLines fileLineTable;

        std::fstream * sourceCode;
        std::fstream * assemblingCode; // TODO: DO I NEED *assemblingCode?
        std::fstream * assembledCode;


        std::uint16_t currentLine = 0;
        uint16_t currentAddress = 0;
        std::string currentToken = "";
        bool isLabelFlag = false;
        bool isInstructionFlag = false;
        bool isConstantFlag = false;
        

        std::string fileName = "binComments.asm";
        
        // TESTING
        void printsMaps();
        
        // END OF TESTING


        std::string currentLineReading,
                typeOfSection,
                comment,
                labelDef,
                instruction, // opcode or value
                arg1,
                arg2,
                vectorSpace;
        FileLines currentFileLine;
        ListOfStrings fromSplit;
        
        


        void onePassAlgorithm();
        bool isEOF();
        void writeAssembledFile();
        
        // TOKEN
        void readFile();

        void getLabelAtLine();
        void getCommentsAtLine();
        void getInstructionAtLine();
        void getArgsAtLine();






        
        bool isInstruction(std::string token);
        bool isDataDirective(std::string token);
        std::string getOpCode(std::string token);
        bool isValidLabel(std::string token);
        bool isDefinition(std::string token);
        bool isValidInstruction(std::string token);
        void operatesLabel(std::string label);
        void operatesInstruction(std::string instruction);
        void operatesConstant(std::string constant);
        
        uint16_t getsSizeVectorSpace();

        // END TOKEN

        void putOnFileLineTable(std::string value);
        void updatesCurrentAddress(
            DirectiveToNumber mapToSizeInMemory,
            uint16_t sizeVector,
            bool isCONST
        );

        void updatesAllUsedPositions();
        void updatesAssembledCodeAtAddress(uint16_t addressValue);
        ListOfStrings getUsedPositionsOfLabel(std::string label);
        void addsToUsedPosition(std::string label, uint16_t address);
        void readTillNextSectionOrEOF();

};

#endif