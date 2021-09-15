#pragma once
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <fstream>
#include <iostream>
#include <map>
#include <symboltable.h>
#include <string>

#define ADDRESS_FILELINE 0
#define OPCODE_FILELINE 1
#define ARG1_FILELINE 2
#define ARG2_FILELINE 3

#define DESIRED_ADDRESS 0
#define ADDRESS_KEY 1

typedef std::vector< std::string> ListOfStrings;
typedef std::map<std::string, uint16_t> DirectiveToNumber;
typedef std::map<std::string, std::string> DirectiveToOpCode;

typedef std::tuple<std::string, std::string> DesiredAddressToKeyAddress;
typedef std::vector<DesiredAddressToKeyAddress> ListOfUsedLabel;


typedef std::tuple<
    std::string, 
    std::string,
    std::string,
    std::string
> AddressOpcodeArgsLine;
// addressKey = getsAddressForLabel()
// listOfPositions = getUsedPositionsFromLabel()

// positionVector = addressDesired - address
// AddressOpcodeArgsLine oldLine = myFile[addressKey]
// FileLines myFile[addressKey]


// map<[addressKey] [address, opcode, arg1, arg2, lineFile]>
// address opcode/value arg1 arg2 lineOriginalFile 
typedef std::map<std::string, AddressOpcodeArgsLine > FileLines;

class Assembler {
    public:
        Assembler(std::fstream *source, std::string fileName);
        ~Assembler();
        void assembleFile();
    private:
        DirectiveToOpCode instructionToOpcode = {
            {"SPACE", "00"},
            {"ADD", "01"},
            {"SUB", "02"},
            {"MULT", "03"},
            {"DIV", "04"},
            {"JMP", "05"},
            {"JMPN", "06"},
            {"JMPP", "07"},
            {"JMPZ", "08"},
            {"COPY", "09"},
            {"LOAD", "10"},
            {"STORE", "11"},
            {"INPUT", "12"},
            {"OUTPUT", "13"},
            {"STOP", "14"}
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
            {"CONST", 1},
        };  


        SymbolTable symbolTable;
        FileLines fileLineTable;

        std::fstream * sourceCode;
        std::fstream * assembledCode;


        uint16_t currentLine = 1;
        std::string currentAddress = "0";
        std::string currentToken = "";        

        std::string fileName = "binComments.asm";
        
        // TESTING
        void printsMaps();
        void printsCurrentLine();
        void printsFileLine(std::string address);
        
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


        void resetLineOperands();
        void getLabelDefAtLine();
        void getCommentsAtLine();
        void getInstructionAtLine();
        void setsSizeVectorSpace(std::string strToBeSearched);
        void setsSizeLine();
        void getArgsAtLine();

        void processLineRead();
        void populatesFileLine();

        void updateCurrentLineAddress();

        // TOKEN

        // VERIFIERS
        bool isValidInstruction(std::string token);
        void validateLabel(std::string token);
        void validateInstruction(std::string token);
        void semanticValidator(); // TODO semanticValidator
        void hasMoreThanOneSameSection(); // TODO hasMoreThanOneSameSection
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

        void updatesAllUsedPositions(std::string label, ListOfUsedLabel usedLabels);
        void updatesAssembledCodeAtAddress(std::string addressValue , DesiredAddressToKeyAddress position);
        void addsToUsedPosition(std::string value, DesiredAddressToKeyAddress position);

};

#endif