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
    DirectiveToOpCode::iterator opcodeMap;
    std::cout << "__________INSTRUCTION TO OPCODE___________"<<std::endl;
    for(
        opcodeMap = this->instructionToOpcode.begin(); 
        opcodeMap != this->instructionToOpcode.end(); 
        ++opcodeMap 
    )
    {
        std::cout << opcodeMap->first << "\t| " 
        <<  opcodeMap->second << std::endl;
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

bool Assembler::isValidInstruction(std::string token) {
    int instructionSize = this->instructToSizeInMemory[token];
    bool isInstruction = instructionSize < 4 && instructionSize > 0;
    bool isSECTION = token == "SECTION";
    return isInstruction || isSECTION;
}

void Assembler::validateInstruction(std::string token) {
    std::string error = "";
    if(token != "") {
        if(!isValidInstruction(token)) {   
            error = "Lexical error at line " + std::to_string(this->currentLine) + ". " + token +" is invalid Instruction.";
            throw error;
        }
    }
}

void Assembler::validateLabel(std::string token) {
    std::string error = "";
    std::string specificError = "";
    int sizeToken = token.size();
    std::regex regexExp("([a-zA-Z_][a-zA-Z0-9_]+)");
    bool hasCorrectChars = std::regex_match(token, regexExp) || this->instruction == "CONST"; 
    bool validLabel = sizeToken <= 50 && hasCorrectChars;
    if(this->isValidInstruction(token) || validLabel) {
        return;
    } else {
        if(sizeToken > 50) specificError += "More than 50 char. ";
        if(!hasCorrectChars) specificError += token +" has invalid Characters. " ;
    }

    error = "Lexical error at line " + std::to_string(this->currentLine) + ". " + specificError;
    throw error;
}

void Assembler::sintaticValidator(uint16_t numOfArgs) {
    uint16_t correctNumArgs = this->instructToSizeInMemory[this->instruction] - 1;
    if(this->instruction == "CONST" || this->instruction == "STOP") correctNumArgs = 1;
    else if(this->instruction == "SPACE") correctNumArgs = this->sizeOfLine;
    else if(this->instruction == "SECTION") this->hasMoreThanOneSameSection();
    else if(numOfArgs != correctNumArgs) {
        std::string error = " Sintatic Error at line " + std::to_string(this->currentLine) + " Expected " + std::to_string(correctNumArgs) + " number of arguments, but instead got "  + std::to_string(numOfArgs);
        throw error;
    }
} 

void Assembler::hasMoreThanOneSameSection() {

  // TODO hasMoreThanOneSameSection  

} 

void Assembler::operatesLabel(
    std::string label,
    uint16_t addressLabelDef,
    bool isDefinition,
    uint16_t labelAddress
) {
    std::string error = "";
    bool isCONSTValue = this->instruction == "CONST" && (addressLabelDef != labelAddress);
    this->validateLabel(label);
    bool isDefined = this->symbolTable.isDefined(label);
    
    DesiredAddressToKeyAddress desiredToKey = std::make_tuple(labelAddress, this->currentAddress);
    
    if(isDefinition && isDefined) {
        error = "Semantic Error at line " + std::to_string(this->currentLine) + ". Label " + label +" already exists";
        throw error;
    } 
    this->symbolTable.adds(
        label,
        addressLabelDef,
        isDefinition,
        {desiredToKey},
        isCONSTValue
    );
    this->populatesFileLine();
    if(isDefined) {     
        uint16_t addressDefKey = this->symbolTable.getsAddressValue(label);   
        // this->updatesAssembledCodeAtAddress(addressDefKey, desiredToKey);
        ListOfUsedLabel listOfPositions = this->symbolTable.getsUsedPositions(label);
        this->updatesAllUsedPositions(addressDefKey, listOfPositions);
    } else 
    if(isDefinition) {
        
        uint16_t addressDefKey = this->symbolTable.getsAddressValue(label);   
        // this->updatesAssembledCodeAtAddress(addressDefKey, desiredToKey);
        ListOfUsedLabel listOfPositions = this->symbolTable.getsUsedPositions(label);

        ListOfUsedLabel allUsedPositions = listOfPositions;
        if(allUsedPositions.empty()) allUsedPositions = {desiredToKey};
        this->updatesAllUsedPositions(addressDefKey, allUsedPositions);

        // std::cout << "GOT HEEERERERERRERE = " << std::endl;
        //     uint16_t addressDefKey = this->symbolTable.getsAddressValue(label);
            
        // std::cout << "addressDefKey = " << addressDefKey << std::endl;
        //     ListOfUsedLabel allUsedPositions = {desiredToKey};
            
        // ListOfUsedLabel listOfPositions = this->symbolTable.getsUsedPositions(label);
        //     ListOfUInts allUsedPositionsSTR = this->symbolTable.fromListOfLabelToUints(allUsedPositions);
        // std::cout << "allUsedPositions = " << getListAsStringUint(allUsedPositionsSTR) << std::endl;
        
        // this->updatesAllUsedPositions(addressDefKey, allUsedPositions);
    }
        
}  

void Assembler::updatesAssembledCodeAtAddress(
    uint16_t addressValueDef, 
    DesiredAddressToKeyAddress position
) {
    uint16_t addressKey = std::get<ADDRESS_KEY>(position);
    // std::cout << "HEREEEEEEEEEEEEEEEEE addressKey = " << addressKey << std::endl;
    // std::cout << "HEREEEEEEEEEEEEEEEEE addressValueDef = " << addressValueDef << std::endl;
    
    if(addressKey < 0) return;
    int addressDesired =  std::get<DESIRED_ADDRESS>(position);    
    int positionAtFileLineTuple =  addressDesired - addressKey;


    

    AddressOpcodeArgsLine oldLine = this->fileLineTable[addressKey];
    uint16_t oldAddress  = std::get<ADDRESS_FILELINE>(oldLine);
    std::string oldOpCODE = std::get<OPCODE_FILELINE>(oldLine);
    std::string newArg1 = std::get<ARG1_FILELINE>(oldLine); 
    std::string newArg2 = std::get<ARG2_FILELINE>(oldLine); 

    if(positionAtFileLineTuple == 1) {
        newArg1 = std::to_string(addressValueDef);
    } else if(positionAtFileLineTuple == 2) {
        newArg2 = std::to_string(addressValueDef);
    }        
    
    // std::cout << "\n\n\nHEREEEEEEEEEEEEEEEEE addressDesired = " << addressDesired << std::endl;
    // std::cout << "HEREEEEEEEEEEEEEEEEE addressValueDef = " << addressValueDef << std::endl;
    // std::cout << "HEREEEEEEEEEEEEEEEEE positionAtFileLineTuple = " << positionAtFileLineTuple << std::endl;
    // std::cout << "HEREEEEEEEEEEEEEEEEE oldAddress = " << oldAddress << std::endl;
    // std::cout << "HEREEEEEEEEEEEEEEEEE oldOpCODE = " << oldOpCODE << std::endl;
    // std::cout << "HEREEEEEEEEEEEEEEEEE newArg1 = " << newArg1 << std::endl;
    // std::cout << "HEREEEEEEEEEEEEEEEEE newArg2 = " << newArg2 << std::endl;
    

    AddressOpcodeArgsLine newLine = make_tuple(
        oldAddress,
        oldOpCODE,
        newArg1,
        newArg2
    );


    // std::cout << "HEREEEEEEEEEEEEEEEEE newArgsList[3] = " << newArgsList[3] << std::endl;
    this->fileLineTable[addressKey] = newLine;
    // this->printsFileLine(addressKey);
    
}

void Assembler::updatesAllUsedPositions(uint16_t addressValueDef, ListOfUsedLabel usedLabels) {
    for(int i = 0; i < usedLabels.size(); i++)
    {
        DesiredAddressToKeyAddress desiredToKey = usedLabels[i];
        
        // std::cout << "\n\n\n\n\n\n\n\n\n\n desired= " << std::get<DESIRED_ADDRESS>(desiredToKey) << std::endl;
        // std::cout << " desiredKEY = " << std::get<ADDRESS_KEY>(desiredToKey) << std::endl;
        this->updatesAssembledCodeAtAddress(addressValueDef, desiredToKey);
    }
}
     

void Assembler::operatesLabelsForLine(
    std::string labelDef,
    std::string arg1,
    std::string arg2
) {
    std::vector <std::tuple <std::string, uint16_t , bool, uint16_t>> labelsTuple;
    bool isDefinition = !labelDef.empty();
    int totalAddress = this->currentAddress;

    if(labelDef != "") labelsTuple.insert(
                labelsTuple.begin(),
                make_tuple(
                    labelDef,
                    this->currentAddress,
                    isDefinition,
                    totalAddress
                )
            );
    if(arg1 != "") labelsTuple.insert(
                labelsTuple.begin(),
                make_tuple(
                    arg1,
                    this->currentAddress,
                    false,
                    totalAddress+1
                )
            );
    if(arg2 != "") labelsTuple.insert(
                labelsTuple.begin(),
                make_tuple(
                    arg2,
                    this->currentAddress,
                    false, 
                    totalAddress+2
                )
            );
    
    if(labelsTuple.size() > 0) {
        for (size_t i = 0; i < labelsTuple.size(); i++) {
            try{
                std::tuple<std::string, uint16_t, bool, uint16_t> currentTuple = labelsTuple[i];
                
                // std::cout <<"PROCESSED LABEL: " << std::get<0>(currentTuple) <<"\t" 
                // << std::get<1>(currentTuple)  <<"\t" << std::get<2>(currentTuple)
                // <<"\t" << std::get<3>(currentTuple) << std::endl;
                this->operatesLabel(
                    std::get<0>(currentTuple),
                    std::get<1>(currentTuple),
                    std::get<2>(currentTuple), 
                    std::get<3>(currentTuple)
                );
            } catch( std::string errmsg ) {
                std::cout << errmsg << '\n';
            }        

        }
    }
}
      
void Assembler::resetLineOperands() {
    this->comment = "";
    this->labelDef = "";
    this->instruction = "";
    this->vectorSpace = "0";
    this->arg1 = "";
    this->arg2 = "";
    this->sizeOfLine = 0;
    this->numberOfArgs = 0;
}

void Assembler::updateCurrentLineAddress() {
    // std::cout << "this->sizeOfLine    \t" << this->sizeOfLine <<std::endl;
    // std::cout << "this->currentAddress    \t" << this->currentAddress <<std::endl;
    if(this->sizeOfLine <=3 && this->sizeOfLine > 0) {
        int vectorSpace = stoi(this->vectorSpace);
        int addressToSum = this->currentAddress;
        // std::cout << "vectorSpace    \t" << vectorSpace <<std::endl;
    
        if(vectorSpace > 0 ){
            addressToSum += vectorSpace;
        } else {
            addressToSum += this->instructToSizeInMemory[this->instruction];
        }
        
        // std::cout << "addressToSum    \t" << addressToSum <<std::endl;
        this->currentAddress = addressToSum;
    }
}

void Assembler::processLineRead() {
    this->populatesFileLine();
    this->operatesLabelsForLine(this->labelDef, this->arg1, this->arg2);

}

void Assembler::populatesFileLine() {
    std::string opCode = this->instructionToOpcode[this->instruction];
    if(this->instruction == "CONST") {
        opCode = this->arg1;
        // this->arg1 = "";
    }
    
    AddressOpcodeArgsLine newLine = make_tuple(
        this->currentAddress,
        opCode,
        this->arg1,
        this->arg2
    );
    this->fileLineTable[this->currentAddress] = newLine;
    // this->printsFileLine(this->currentAddress);
}

void Assembler::printsFileLine(uint16_t address) {
    uint16_t addressKey = address;
    AddressOpcodeArgsLine fileLineToPrint = this->fileLineTable[addressKey];

    std::cout << "\tAddress:" << std::get<ADDRESS_FILELINE>(fileLineToPrint)
    << "\tinstruction:" << std::get<OPCODE_FILELINE>(fileLineToPrint)  << "   "
    << "\targ1:" << std::get<ARG1_FILELINE>(fileLineToPrint) << "     "
    << "arg2:" << std::get<ARG2_FILELINE>(fileLineToPrint) << std::endl;

}

void Assembler::printsCurrentLine() {
    std::cout << "\tLine:" << this->currentLine
    << "\tAddress:" << this->currentAddress 
    << "\tlabelDef:[" << this->labelDef <<"]"
    << "\tinstruction:" << this->instruction  << "   "
    << "\targ1:" << this->arg1 << "     "
    << "arg2:" << this->arg2 << std::endl;
}

void Assembler::setsSizeLine() {
    // std::cout << "HEREEEEEEEEEEEEEE" << std::endl;
    if(this->vectorSpace != "0") {
        this->sizeOfLine = stoi(this->vectorSpace);
    } else{
        this->sizeOfLine = this->instructToSizeInMemory[this->instruction];
    }
}

void Assembler::onePassAlgorithm(){
  
    // this->symbolTable.printTable();  
    this->shouldWriteFile = true;
    while(std::getline(*(this->sourceCode), this->currentLineReading)) {
        try{
            this->resetLineOperands();
            
            this->currentLineReading = removeMultipleSpaces(this->currentLineReading);
            this->getCommentsAtLine();
            this->getLabelDefAtLine();
            
            this->getInstructionAtLine();

            this->setsSizeLine();
            this->getArgsAtLine();

            this->printsCurrentLine();

            this->processLineRead();
            this->updateCurrentLineAddress();


            this->currentLine +=1;
        } catch( std::string errmsg ) {
            this->shouldWriteFile = false;
            std::cout << errmsg << '\n';
        }        
        // std::cout << "fromSplit    \t" << getListAsString(fromSplit) << "\tSIZE LIST: " << fromSplit.size() <<std::endl;
    }


    this->symbolTable.printTable();     

    // std::sort(this->fileLineTable.begin(), this->fileLineTable.end(), myfunction);

    for (FileLines::iterator it = this->fileLineTable.begin(); it != this->fileLineTable.end(); it++ )
    {
        this->printsFileLine(it->first);
    }
             
}


void Assembler::getLabelDefAtLine() {
    if (this->currentLineReading.empty()) return;
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
    if (this->currentLineReading.empty()) return;
    
    bool instructionFound = false;
    bool isSPACE = false;
    bool isCONST = false;
    bool isSECTION = false;
    bool isCOPY = false;
    bool isSTOP = false;
    this->currentLineReading = trimFirstAndLastWhiteSpace(this->currentLineReading);
    this->fromSplit = split(this->currentLineReading, ' ');

    isSTOP = this->fromSplit.at(0) == "STOP";
    instructionFound = this->fromSplit.size() > 1;
    isSPACE = this->fromSplit.at(0).find("SPACE") != std::string::npos;
    isSECTION = this->fromSplit.at(0) == "SECTION";
    isCOPY = this->fromSplit.at(0) == "COPY";
    
    if(isSTOP) this->instruction = this->fromSplit.at(0);
        
    if(instructionFound) {
        this->instruction = this->fromSplit.at(0);
        
        if(isSECTION) {
            this->typeOfSection = this->fromSplit.at(1);
            // this->currentLineReading = this->fromSplit.at(1);
        } 
        // else if(isCOPY) {
        //     std::cout << "this->fromSplit " << getListAsString(this->fromSplit) <<std::endl;
        //     this->currentLineReading = (this->fromSplit.at(1));
        // } 
        this->currentLineReading = this->fromSplit.at(1);
        
    // } 
    // else if (isSTOP) {
    //         this->instruction = "STOP";
    //         // std::cout << "INSTRUCTION:\t instruction    \t" << this->instruction <<std::endl;
    //         this->currentLineReading = this->fromSplit.at(0);
    } else if (isSPACE) {
        this->instruction = "SPACE";
        this->setsSizeVectorSpace(this->fromSplit.at(0));
        // std::cout << "instruction    \t" << this->instruction <<std::endl;
        this->currentLineReading = this->fromSplit.at(0);
    } else {
        this->currentLineReading = this->fromSplit.at(0);
    }

    
            // std::cout << "222222222222222222    " <<std::endl;

    this->validateInstruction(this->instruction);
    // std::cout << "currentLineReading    \t" << this->currentLineReading <<std::endl;
    // std::cout << "instruction    \t" << this->instruction <<std::endl;
    // std::cout << "INSTRUCTION:\t fromSplit    \t" << getListAsString(this->fromSplit) << "\tSIZE LIST: " << fromSplit.size() <<std::endl;
    this->currentLineReading = removeAllSpaces(this->currentLineReading);
}

void Assembler::getArgsAtLine() {
    if (this->currentLineReading.empty()) return;
    this->numberOfArgs = this->sizeOfLine - 1;
    bool isCONST = this->instruction == "CONST";
    bool isSPACE = this->instruction == "SPACE";
    bool isSTOP = this->instruction == "STOP";
    bool shouldReadArgs = !isSPACE && !isSTOP &&
    (isCONST || (this->numberOfArgs != 0 && this->numberOfArgs < 3));
    this->fromSplit = split(this->currentLineReading, ',');

    this->sintaticValidator(this->fromSplit.size());
    if(shouldReadArgs) {
        if (this->numberOfArgs == 2) {
            this->arg1 = this->fromSplit.at(0);
            this->arg2 = this->fromSplit.at(1);
            this->currentLineReading = this->fromSplit.at(1);
        } else {
            this->arg1 = this->fromSplit.at(0);
            this->arg2 = "";
            this->currentLineReading = this->fromSplit.at(0);
        }
    }
    
}

void Assembler::writeAssembledFile() {
    std::string finalFileName = this->fileName.substr(0,this->fileName.find_last_of('.'))+".obj";
    std::fstream output;
    output.open(finalFileName,std::ios::out );

    std::cout << "\n OUTPUTING FILE \n\n\n" << std::endl;
        

    FileLines::iterator it = this->fileLineTable.begin();
    while (it != this->fileLineTable.end())
    {
        uint16_t key = it->first;
        AddressOpcodeArgsLine lineToWrite = it->second;
        uint16_t address  = std::get<ADDRESS_FILELINE>(lineToWrite);
        std::string opCODE = std::get<OPCODE_FILELINE>(lineToWrite);
        std::string arg1 = std::get<ARG1_FILELINE>(lineToWrite); 
        std::string arg2 = std::get<ARG2_FILELINE>(lineToWrite); 

        bool isCONST = arg1 == opCODE;
        
        std::string outputString = opCODE + " ";
        if(!arg1.empty() && !isCONST) outputString += arg1 + " ";
        if(!arg2.empty()) outputString += arg2 + " ";
        
        output << outputString;

        it++;
    }
    output.close();
    this->canSimulate = true;
    std::cout << "[check] .obj file written"<<std::endl;
}


void Assembler::assembleFile(){
    this->onePassAlgorithm();
    if(this->shouldWriteFile) this->writeAssembledFile();
    else std::cout << "Assembling ended with errors."<<std::endl;
}


