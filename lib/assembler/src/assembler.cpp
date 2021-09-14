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

bool Assembler::isValidInstruction(std::string token) {
    // TODO isValidLabel
    return false;
}

uint16_t Assembler::getsSizeVectorSpace() {
    return 0;
}

void Assembler::operatesInstruction(std::string instruction) {
    this->isValidInstruction(instruction);
    DirectiveToNumber mapToSizeInMemory = this->dataToSizeInMemory;
    uint16_t sizeVector = 0;
    bool isCONST = 0;
    if(this->currentToken == "SPACE") {
        sizeVector = this->getsSizeVectorSpace();
    } else if(this->currentToken == "CONST") {
        isCONST = 1;
    } else {
        mapToSizeInMemory = this->instructToSizeInMemory;
    }
    this->updatesCurrentAddress(mapToSizeInMemory, sizeVector, isCONST);
}

void Assembler::operatesConstant(std::string constant) {
    this->putOnFileLineTable(constant);
    std::cout << this->currentToken <<"\t\t" << this->currentLine <<"\t" << this->currentAddress <<std::endl;
}

void Assembler::putOnFileLineTable(std::string value) {

}
       

void Assembler::onePassAlgorithm(){
    this->readToken();
    bool isDefined = this->symbolTable.isDefined(this->currentToken);
    bool isDefinition = this->isDefinition(this->currentToken);
    std::cout << "TOKEN\t\t LINE\t ADDRESS\t"<<std::endl;
            
    while( !this->isEOF() ) {    
        if( isDefined && isDefinition ) {
            throw ("Semantic Exception at line %d", currentLine);
        }
        if(this->isLabelFlag) {
            this->operatesLabel(this->currentToken);
        } else if(this->isInstructionFlag) {
            this->operatesInstruction(this->currentToken);
        } else if(this->isConstantFlag) {
            this->operatesConstant(this->currentToken);
        }        
        this->readToken();
    }
}

bool Assembler::isDefinition(std::string token){
    return false; // TODO isDefinition
}

bool Assembler::isEOF() {
    return this->sourceCode->eof();
}

bool Assembler::isNumber(std::string stringToTest) {
    std::regex rx("([0-9])");
    std::smatch m;
    bool isNumber = std::regex_match(stringToTest, rx);
    return isNumber;
}

void Assembler::processToken(char currentChar) {

    this->isLabelFlag = false;
    this->isInstructionFlag = false;
    this->isConstantFlag = false;

    if(this->isNumber(this->currentToken)) {
        this->isConstantFlag =  true;
    } else {
        if(currentChar == ':') {
            this->isLabelFlag = true;
        } 
        else if(currentChar == ' ') {
            if(this->isInstruction(this->currentToken)) {
                this->isInstructionFlag = true;
            }
        } else if(currentChar == '\n') {
            this->isLabelFlag = true;
        } else if(currentChar == ',') {

        } else if(currentChar ==  ';') {
            std::string comment;
            std::getline(*(this->sourceCode), comment);
        } else if(currentChar ==  '\n') {
            this->currentLine++;
        } 
    }   

    // if(this->isLabelFlag) {
    //     std::cout << "isLabel"<<std::endl;
    // } else if(this->isInstructionFlag) {
    //     std::cout << "isInstruction"<<std::endl;
    // } else if(this->isConstantFlag) {
    //     std::cout << "isConstant"<<std::endl;
    // }
}

bool Assembler::isInstruction(std::string token) {
    DirectiveToNumber instructionMap = this->instructionToOpcode;
    if(instructionMap.find(token) != instructionMap.end()) {
        return true;
    }
    return false;
}

bool Assembler::isDataDirective(std::string token) {
    DirectiveToNumber instructionMap = this->instructionToOpcode;
    if(instructionMap.find(token) != instructionMap.end()) {
        return true;
    }
    return false;
}

void Assembler::readToken() {
    std::string currentLine,
                typeOfSection,
                comment,
                labelDef,
                opcodeValue,
                arg1,
                arg2;
    FileLines currentFileLine;
    ListOfStrings fromSplit;
    while(std::getline(*(this->sourceCode), currentLine)) {
        currentLine = removeMultipleSpaces(currentLine);
        // COMMENTS
        fromSplit = split(currentLine, ';');
        currentLine = fromSplit.at(0);

        //TYPEOFSECTION
        
        fromSplit = split(currentLine, ':');
        if(fromSplit.size() > 1) { // FOUND LABEL DEF
            labelDef = fromSplit.at(0);
            std::cout << "Label    \t" << labelDef <<std::endl;
            currentLine = fromSplit.at(1);
        } else { // SAME STRING
            currentLine = fromSplit.at(0);
        }


        // LABEL DEF

        std::cout << "currentLine    \t" << currentLine <<std::endl;
        fromSplit = split(currentLine, ':');
        if(fromSplit.size() > 1) { // FOUND LABEL DEF
            labelDef = fromSplit.at(0);
            std::cout << "Label    \t" << labelDef <<std::endl;
            currentLine = fromSplit.at(1);
        } else { // SAME STRING
            currentLine = fromSplit.at(0);
        }

        // SPACES
        fromSplit = split(currentLine, ' ');
        std::cout << "fromSplit SPACE\t" << getListAsString(fromSplit) << "\tSIZE LIST: " << fromSplit.size() <<std::endl;

        // if(fromSplit.size() > 1) { // FOUND LABEL DEF
        //     labelDef = fromSplit.at(0);
        //     std::cout << "Label    \t" << labelDef <<std::endl;
        //     currentLine = fromSplit.at(1);
        // } else { // SAME STRING
        //     currentLine = fromSplit.at(0);
        // }





        // std::cout << "fromSplit    \t" << getListAsString(fromSplit) << "\tSIZE LIST: " << fromSplit.size() <<std::endl;

    }



    // char c;
    // bool exitChar = false;
    // this->currentToken.clear();
    // std::string currentCharString;
    // while(!exitChar){
    //     this->sourceCode->get(c);
    //     exitChar = c == ':' 
    //     || c == ' ' 
    //     || c == ';'
    //     || c == ','
    //     || c == '\n';
    //     if(exitChar) {
    //         this->processToken(c);
    //     } else {
    //         if(!this->isEOF()) { 
    //             currentCharString = ("%c", c);
    //             this->currentToken += currentCharString;  
    //         } else {
    //             exitChar = true;
    //         }
    //     }
    // }
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


