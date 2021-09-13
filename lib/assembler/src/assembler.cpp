#include <assembler.h>
#include <fstream>
#include <iostream>
#include <string>

Assembler::~Assembler(){}
Assembler::Assembler(std::fstream *source, std::string fileName){
    this->sourceCode = source;
    this->fileName = fileName;
    std::cout << "Assembler Set"<< std::endl;
}
void Assembler::onePassAlgorithm(){
    std::string currentToken;
    std::uint16_t currentLine;

    uint16_t position = 0;
    uint16_t currentAddress = 0;

    std::string label;
    uint16_t value;
    bool setDefined; 
    ListOfStrings listOfUse;

    currentToken = this->readToken();
    bool isDefined = this->symbolTable.isDefined(label);
    bool isDefinition = this->isDefinition(label);

    while( !this->isEOF() ) {
        if( isDefined && isDefinition ) {
            throw ("Semantic Exception at line %d", currentLine);
        }
        if(!this->symbolTable.contains(currentToken)) {
            this->symbolTable.adds(label, value, isDefined, listOfUse);
        }
        if(isDefined) {
            std::uint16_t addressValue = this->symbolTable.getsAddressValue(label);
            this->updatesAssembledCodeAtPosition(position, addressValue);
        } else if(isDefinition){
            setDefined = true;
            updatesAllUsedPositions();
        } else {
            addsToUsedPosition(label, currentAddress);
        }
    }
}

bool Assembler::isDefinition(std::string token){
    return false;
}

bool Assembler::isEOF() {
    // TODO isEOF
    return true;
}

std::string Assembler::readToken() {
    // TODO readToken
    return "false";
}

void Assembler::updatesAssembledCodeAtPosition(uint16_t position, uint16_t addressValue) {
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


