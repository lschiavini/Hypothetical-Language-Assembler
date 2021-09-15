#pragma once
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <fstream>
#include <iostream>
#include <map>
#include <symboltable.h>
#include <string>

typedef std::vector< std::string> ListOfStrings;
typedef std::map<std::string, uint16_t> DirectiveToNumber;


typedef std::tuple<std::string, std::string, std::string, std::string, uint16_t > AddressOpcodeArgsLine;
// address opcode/value arg1 arg2 lineOriginalFile 
typedef std::map<std::string, AddressOpcodeArgsLine > FileLines;

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


        uint16_t currentLine = 1;
        std::string currentAddress = "0";
        std::string currentToken = "";        

        std::string fileName = "binComments.asm";
        
        // TESTING
        void printsMaps();
        void printsCurrentLine();
        
        // END OF TESTING


        std::string currentLineReading,
                typeOfSection,
                comment,
                labelDef,
                instruction, // opcode or value
                vectorSpace,
                arg1,
                arg2;
        uint16_t numberOfArgs, sizeOfLine;
        ListOfStrings fromSplit;

        void onePassAlgorithm();
        void writeAssembledFile();
        void processLineRead();


        // TOKEN
        void resetLineOperands();

        void getLabelDefAtLine();
        void getCommentsAtLine();
        void getInstructionAtLine();
        void setsSizeVectorSpace(std::string strToBeSearched);
        void setsSizeLine();
        void getArgsAtLine();

        void updateCurrentLineAddress();


            // VERIFIERS
            bool isDataDirective(std::string token);
            bool isValidInstruction(std::string token);
            void validateLabel(std::string token);
            void validateInstruction(std::string token);
            void semanticValidator(); // TODO semanticValidator
            // END VERIFIERS

        
        std::string getOpCode(std::string token);
        void operatesLabelsForLine(
            std::string labelDef,
            std::string arg1,
            std::string arg2
        );

        void operatesLabel(
            std::string label,
            std::string addressLabelDef,
            bool isDefinition,
            std::string labelAddress
        );
        void operatesInstruction(std::string instruction);
        void operatesConstant(std::string constant);
        
        
        // END TOKEN

        void putOnFileLineTable(std::string value);
        void updatesCurrentAddress(
            DirectiveToNumber mapToSizeInMemory,
            uint16_t sizeVector,
            bool isCONST
        );

        void updatesAllUsedPositions();
        void updatesAssembledCodeAtAddress(std::string addressValue);
        ListOfStrings getUsedPositionsOfLabel(std::string label);
        void addsToUsedPosition(std::string label, std::string address);
        void readTillNextSectionOrEOF();

};

#endif