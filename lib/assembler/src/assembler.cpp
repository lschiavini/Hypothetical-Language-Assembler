#include <assembler.h>
#include <stringUtils.h>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <sstream>


Assembler::~Assembler(){}
Assembler::Assembler(std::fstream *source, std::string fileName){
    this->sourceCode = source;
    this->fileName = fileName;
    // this->printsMaps();
    std::cout << "Assembler Set"<< std::endl;
}

void Assembler::printsMaps() {
    DirectiveToNumber::iterator iteratorMap;
    std::cout << "__________INSTRUCTION TO OPCODE___________"<<std::endl;
    for(
        iteratorMap = this->instructionToOpcode.begin(); 
        iteratorMap != this->instructionToOpcode.end(); 
        ++iteratorMap 
    )
    {
        std::cout << iteratorMap->first << "\t| " 
        <<  iteratorMap->second << std::endl;
    } 
    std::cout << "_____________________"<<std::endl;


    std::cout << "__________INSTRUCTION TO SIZE IN MEMORY___________"<<std::endl;
    for(
        iteratorMap = this->instructToSizeInMemory.begin(); 
        iteratorMap != this->instructToSizeInMemory.end(); 
        ++iteratorMap 
    )
    {
        std::cout << iteratorMap->first << "\t| " 
        <<  iteratorMap->second << std::endl;
    } 
    std::cout << "_____________________"<<std::endl;

}


void Assembler::updatesCurrentAddress(
    DirectiveToNumber mapToSizeInMemory,
    uint16_t sizeVector,
    bool isCONST
) {
    if (!this->currentToken.empty()) {
        if (isCONST) {
            this->currentAddress += 1;
        } else {
            this->currentAddress += mapToSizeInMemory[this->currentToken] + sizeVector;
        }
    }
}

bool Assembler::isValidLabel(std::string token) {
    // TODO isValidLabel
    return false;
}

void Assembler::operatesLabel(std::string label) {
    bool setDefined = false; 
    uint16_t addressValue = this->currentAddress;
    bool isDefined = this->symbolTable.isDefined(this->currentToken);
    bool isDefinition = this->isDefinition(this->currentToken);
    ListOfStrings listOfUse;

    this->isValidLabel(label);

    if(!this->symbolTable.contains(this->currentToken)) {
        this->symbolTable.adds(label, addressValue, setDefined, listOfUse);
    }
    if(isDefined) {
        std::uint16_t addressValue = this->symbolTable.getsAddressValue(label);
        this->updatesAssembledCodeAtAddress(addressValue);
    } else if(isDefinition){
        setDefined = true;
        updatesAllUsedPositions();
    } else {
        addsToUsedPosition(label, this->currentAddress);
    }
    // TODO operatesLabel
    std::cout << this->currentToken <<"\t\t" << this->currentLine <<"\t" << this->currentAddress <<std::endl;

}



// void Assembler::operatesInstruction(std::string instruction) {
//     this->isValidInstruction(instruction);
//     DirectiveToNumber mapToSizeInMemory = this->dataToSizeInMemory;
//     uint16_t sizeVector = 0;
//     bool isCONST = 0;
//     if(this->currentToken == "SPACE") {
//         sizeVector = this->getsSizeVectorSpace();
//     } else if(this->currentToken == "CONST") {
//         isCONST = 1;
//     } else {
//         mapToSizeInMemory = this->instructToSizeInMemory;
//     }
//     this->updatesCurrentAddress(mapToSizeInMemory, sizeVector, isCONST);
// }

// void Assembler::operatesConstant(std::string constant) {
//     this->putOnFileLineTable(constant);
//     std::cout << this->currentToken <<"\t\t" << this->currentLine <<"\t" << this->currentAddress <<std::endl;
// }

// void Assembler::putOnFileLineTable(std::string value) {

// }
       

void Assembler::onePassAlgorithm(){


    bool isDefined = this->symbolTable.isDefined(this->labelDef);
    bool isDefinition = this->isDefinition(this->currentToken);
    
    while(std::getline(*(this->sourceCode), this->currentLineReading)) {
        this->currentLineReading = removeMultipleSpaces(this->currentLineReading);
        std::cout << "currentLineReading    \t" << this->currentLineReading <<std::endl;
        std::cout << std::endl;
        this->getCommentsAtLine();
        this->getLabelDefAtLine();
        this->getInstructionAtLine();
        this->numberOfArgs = this->instructToSizeInMemory[this->instruction] - 1;
        std::cout << "this->instruction    \t" << this->instruction <<std::endl;
        if(this->numberOfArgs != 0 && this->numberOfArgs < 3) this->getArgsAtLine();


        // std::cout << "fromSplit    \t" << getListAsString(fromSplit) << "\tSIZE LIST: " << fromSplit.size() <<std::endl;

    }

    // bool isDefined = this->symbolTable.isDefined(this->currentToken);
    // bool isDefinition = this->isDefinition(this->currentToken);
    // std::cout << "TOKEN\t\t LINE\t ADDRESS\t"<<std::endl;
            
    // while( !this->isEOF() ) {    
    //     if( isDefined && isDefinition ) {
    //         throw ("Semantic Exception at line %d", currentLine);
    //     }
    //     if(this->isLabelFlag) {
    //         this->operatesLabel(this->currentToken);
    //     } else if(this->isInstructionFlag) {
    //         this->operatesInstruction(this->currentToken);
    //     } else if(this->isConstantFlag) {
    //         this->operatesConstant(this->currentToken);
    //     }        
    //     this->readFile();
    // }
}

bool Assembler::isDefinition(std::string token){
    return false; // TODO isDefinition
}


bool Assembler::isValidInstruction(std::string token) { 
    DirectiveToNumber instructionMap = this->instructionToOpcode;
    if(instructionMap.find(token) != instructionMap.end()) {
        return true;
    }
    return false;
    // TODO: throw error at line
}

bool Assembler::isDataDirective(std::string token) {
    DirectiveToNumber instructionMap = this->instructionToOpcode;
    if(instructionMap.find(token) != instructionMap.end()) {
        return true;
    }
    return false;
}

void Assembler::getLabelDefAtLine() {
    bool foundLabel = false;
    this->fromSplit = split(this->currentLineReading, ':');
    foundLabel = this->fromSplit.size() > 1;
    if(foundLabel) {
        this->labelDef = this->fromSplit.at(0);
        // std::cout << "Label    \t" << this->labelDef <<std::endl;
        this->currentLineReading = this->fromSplit.at(1);
    } else {
        this->currentLineReading = this->fromSplit.at(0);
    }
    // std::cout << "currentLineReading    \t" << this->currentLineReading <<std::endl;
    
}

void Assembler::getCommentsAtLine() {
    this->fromSplit = split(this->currentLineReading, ';');
    this->currentLineReading = this->fromSplit.at(0);
    // std::cout << "currentLineReading    \t" << this->currentLineReading <<std::endl;
    
}

void Assembler::setsSizeVectorSpace(std::string strToBeSearched) {
    std::string vectorValue = "0";
    ListOfStrings newStringList;
    uint16_t posPlus = strToBeSearched.find("+"); 
    // std::cout << "strToBeSearched    \t" << strToBeSearched <<std::endl;
    // std::cout << "posPlus    \t" << posPlus <<std::endl;
    
    if(posPlus < 60000) {
        newStringList = split(strToBeSearched, '+');
        vectorValue = newStringList.at(1);
        this->vectorSpace = vectorValue;
        // std::cout << "this->vectorSpace    \t" << this->vectorSpace <<std::endl;
    }
}

void Assembler::getInstructionAtLine() {
    bool instructionFound = false;
    bool isSPACE = false;
    bool isSECTION = false;
    bool isCOPY = false;
    bool isSTOP = false;
    this->currentLineReading = trimFirstAndLastWhiteSpace(this->currentLineReading);
    this->fromSplit = split(this->currentLineReading, ' ');

    instructionFound = this->fromSplit.size() > 1;
    isSPACE = this->fromSplit.at(0).find("SPACE") != std::string::npos;
    isSECTION = this->fromSplit.at(0) == "SECTION";
    isCOPY = this->fromSplit.at(0) == "COPY";
    isSTOP = this->fromSplit.at(0) == "STOP";
    
    // std::cout << "INSTRUCTION:\t currentLineReading    \t" << this->currentLineReading <<std::endl;
    
    if(instructionFound) {
        this->instruction = this->fromSplit.at(0);
        if(isSECTION) {
            this->typeOfSection = this->fromSplit.at(1);
            this->currentLineReading = this->fromSplit.at(1);
            // std::cout << "typeOfSection    \t" << this->typeOfSection <<std::endl;
        } else if(isCOPY) {
            this->currentLineReading = (this->fromSplit.at(1)).append(this->fromSplit.at(2));
        } 
        // std::cout << "instruction    \t" << this->instruction <<std::endl;
        this->currentLineReading = this->fromSplit.at(1);
    } else if (isSTOP) {
            this->instruction = "STOP";
            // std::cout << "INSTRUCTION:\t instruction    \t" << this->instruction <<std::endl;
            this->currentLineReading = this->fromSplit.at(0);
    } else if (isSPACE) {
        this->instruction = "SPACE";
        this->setsSizeVectorSpace(this->fromSplit.at(0));
        // std::cout << "instruction    \t" << this->instruction <<std::endl;
        this->currentLineReading = this->fromSplit.at(0);
    } else {
        this->currentLineReading = this->fromSplit.at(0);
    }
    // std::cout << "INSTRUCTION:\t fromSplit    \t" << getListAsString(this->fromSplit) << "\tSIZE LIST: " << fromSplit.size() <<std::endl;
    this->currentLineReading = removeAllSpaces(this->currentLineReading);
    
}

void Assembler::getArgsAtLine() { // could find labelsInline

    std::cout << "ARGS:\t numberOfArgs    \t" << this->numberOfArgs <<std::endl;
    this->fromSplit = split(this->currentLineReading, ',');
    std::cout << "ARGS:\t fromSplit    \t" << getListAsString(this->fromSplit) << "\tSIZE LIST: " << fromSplit.size() <<std::endl;

    if (this->numberOfArgs == 2) {
        this->arg1 = this->fromSplit.at(0);
        this->arg2 = this->fromSplit.at(1);
        this->currentLineReading = this->fromSplit.at(1);
    } else {
        this->arg1 = this->fromSplit.at(0);
        this->arg2 = "";
        this->currentLineReading = this->fromSplit.at(0);
    }
    std::cout << "ARGS:\t Args\t" << this->arg1 << " " <<  this->arg2 <<std::endl;
    
    std::cout << "ARGS:\t fromSplit    \t" << getListAsString(this->fromSplit) << "\tSIZE LIST: " << fromSplit.size() <<std::endl;

}


void Assembler::updatesAssembledCodeAtAddress(uint16_t addressValue) {
    // TODO updatesAssembledCodeAtPosition
}

void Assembler::updatesAllUsedPositions() {

    // TODO updatesAllUsedPositions
}

void Assembler::addsToUsedPosition(std::string label, uint16_t address) {
    // TODO addsToUsedPosition
}

void Assembler::writeAssembledFile() {
    std::string finalFileName = this->fileName.substr(0,this->fileName.find_last_of('.'))+".obj";
    std::fstream output;
    output.open(finalFileName,std::ios::out );

    //TODO writeAssembledFile

    output.close();
    std::cout << "[check] .obj file written"<<std::endl;
}

void Assembler::assembleFile(){
    this->onePassAlgorithm();
    this->writeAssembledFile();
}


