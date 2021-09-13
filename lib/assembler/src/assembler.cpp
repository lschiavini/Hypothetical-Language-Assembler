#include <assembler.h>
#include <fstream>
#include <iostream>
#include <string>

Assembler::~Assembler(){}
Assembler::Assembler(std::fstream *source, std::string fileName){
    this->sourceCode = source;
    this->fileName = fileName;
    // this->printsMaps();
    std::cout << "Assembler Set"<< std::endl;
}

void Assembler::printsMaps() {
    InstructionToNumber::iterator iteratorMap;
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


void Assembler::onePassAlgorithm(){

    uint16_t position = 0;
    std::string label;
    uint16_t addressValue;
    bool setDefined; 
    ListOfStrings listOfUse;

    this->readToken();
    
    bool isDefined = this->symbolTable.isDefined(this->currentToken);
    bool isDefinition = this->isDefinition(this->currentToken);

    while( !this->isEOF() ) {

        
        if( isDefined && isDefinition ) {
            throw ("Semantic Exception at line %d", currentLine);
        }
        if(!this->symbolTable.contains(this->currentToken)) {
            this->symbolTable.adds(label, addressValue, isDefined, listOfUse);
        }
        if(isDefined) {
            std::uint16_t addressValue = this->symbolTable.getsAddressValue(label);
            this->updatesAssembledCodeAtPosition(position, addressValue);
        } else if(isDefinition){
            setDefined = true;
            updatesAllUsedPositions();
        } else {
            addsToUsedPosition(label, this->currentAddress);
        }

        
        this->currentLine++;
        this->currentAddress += this->instructToSizeInMemory[label];
        this->readToken();
    }
}

bool Assembler::isDefinition(std::string token){
    return false;
}

bool Assembler::isEOF() {
    return this->sourceCode->eof();
}

void Assembler::readToken() {
    char c;
    bool endWhile = false;
    this->currentToken.clear();
    std::string currentChar;
    while(!endWhile){
        this->sourceCode->get(c);
        endWhile = c == ':' 
        || c == ' ' 
        || c == ';'
        || c == ','
        || c == '\n';

        if(c == ':') {
            
        } 
        else if(c == ' ') {

        } else if(c == '\n') {

        } else if(c == ',') {

        } else if(c ==  ';') {
            std::string comment;
            std::getline(*(this->sourceCode), comment);
        } else if(!this->isEOF()) {
            currentChar = ("%c", c);
            this->currentToken += currentChar;            
        }

        if(endWhile) {
            // this->sourceCode->unget();
        } else if(this->isEOF()) {
            endWhile = true;
        }
    }

    if (!this->currentToken.empty()) {
        std::cout << "Current Token: " << this->currentToken <<std::endl;
    }
    
    // TODO readToken
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


