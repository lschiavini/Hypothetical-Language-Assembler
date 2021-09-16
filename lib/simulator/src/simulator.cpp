#include <simulator.h>
#include <fstream>
#include <iostream>
#include <string>

Simulator::~Simulator(){}
Simulator::Simulator(std::string fileName){
    std::cout << "Simulating with [" << fileName << "]" <<std::endl;
    this->fileName = fileName;
    std::vector<std::string> fileNameVector =  split(fileName, '/');
    this->fileDir =  fileNameVector.at(0) + '/' + fileNameVector.at(1) + '/';
    fileNameVector = split(fileNameVector.at(2), '.');
    std::string newfileNameStr = fileNameVector.at(0) + ".obj";
    this->fileName = "" + newfileNameStr;
    
}
void Simulator::simulate() {
    this->setFileContents();
    this->setFileLines();
    this->printFileLines();
    std::cout << "\n\nRunning" <<std::endl;
    this->execute();
}

void Simulator::printCurrentOperation() {
    std::cout << "PC : " << this->PC << " "
    << "ACC : " << this->ACC << " "
    <<"\n" << getListAsString(this->fileContents) << std::endl;
}

int Simulator::safeSTOI(std::string stringToParse) {
    try{
        if(stringToParse.empty()) return 0;
        return stoi(stringToParse);
    } catch(std::exception error) {
        return 0;
    }
    
}

void Simulator::execute() {
    FileLines::iterator it = this->fileLines.begin();
    std::string instruction = "0";
    std::string arg1S = "";
    std::string arg2S = "";
    int arg1 = 0;
    int arg2 = 0;
    this->PC = 0;
    
    while(!this->reachedSTOP) {
        AddressOpcodeArgsLine currLine = this->fileLines[this->PC];
        instruction = std::get<1>(currLine);
        arg1 = this->safeSTOI(std::get<2>(currLine));
        arg2 = this->safeSTOI(std::get<3>(currLine));
        if(instruction == "ADD") {
            this->MEM = arg1;
            this->ACC = this->ACC + this->MEM;
        } else if(instruction == "SUB") {
            this->MEM = arg1;
            this->ACC = this->ACC - this->MEM;
        }else if(instruction == "MULT") {
            this->MEM = arg1;
            this->ACC = this->ACC * this->MEM;
        }else if(instruction == "DIV") {
            this->MEM = arg1;
            this->ACC = this->ACC / this->MEM;
        }else if(instruction == "JMP") {
            this->PC = arg1;
        }else if(instruction == "JMPN") {
            if(this->ACC < 0) this->PC = arg1;
        }else if(instruction == "JMPP") {
            if(this->ACC > 0) this->PC = arg1;
        }else if(instruction == "JMPZ") {
            if(this->ACC == 0) this->PC = arg1;
        }else if(instruction == "COPY") {
            this->fileContents[arg2] = this->fileContents[arg1];
        }else if(instruction == "LOAD") {
            std::cout << "AAAAAAAAAAA " << this->fileContents[arg1] << std::endl;
            this->ACC = this->safeSTOI(this->fileContents[arg1]);
        }else if(instruction == "STORE") {
            this->fileContents[arg1] = this->ACC;
        }else if(instruction == "INPUT") {
            std::string userInput = "";
            std::cout << "Type a number: ";
            std::cin >> userInput;
            this->fileContents[arg1] = userInput;
        }else if(instruction == "OUTPUT") {
            std::string userInput = "";
            this->OUTPUT = this->fileContents[arg1];
            std::cout  << "OUTPUT : " << this->OUTPUT << " " <<std::endl;
            std::cout << "Type a Enter ";
            std::cin >> userInput;
        }else if(instruction == "STOP") {
            this->reachedSTOP = true;
        }
        this->printCurrentOperation();
    }
}

void Simulator::setFileContents() {
    std::string pathToFile = (this->fileDir + this->fileName);
    this->input.open(pathToFile, std::ios::in);
    std::cout << "\n\nSimulating with [" << pathToFile  << "]" <<std::endl;
    while(std::getline(this->input, this->fileContentsStrint));
    this->input.close();
    this->fileContents = split(this->fileContentsStrint, ' ');
    std::cout << "fileContents with [" << getListAsString(this->fileContents)  << "]" <<std::endl;
    std::cout << "fileContents size [" << this->fileContents.size()  << "]" <<std::endl;
}


void Simulator::setFileLines() {
    uint16_t pc = 0;
    std::string instruction = "";
    std::string arg1 = "";
    std::string arg2 = "";
    bool isCONST = false;

    for(int i = 0; i <= this->fileContents.size() ; i++) {
        i = pc;
        isCONST = false;
        if(instruction == "STOP") isCONST = true;
        instruction = "";
        arg1 = "";
        arg2 = "";
        
        // std::cout << "line at position = "<< i <<std::endl;
        // std::cout << "this->fileContents[i] = "<< this->fileContents[i] <<std::endl;


        if(isCONST) {
            instruction = this->fileContents[i];
            arg1 = "";
            arg2 = "";
            i+=1;
        } else if(this->opcodeToInstruction.find(this->fileContents[i]) != this->opcodeToInstruction.end()) {
            instruction = this->opcodeToInstruction[this->fileContents[i]];
            uint16_t numOfArgs = this->instructToSizeInMemory[instruction] - 1;
            // std::cout << "numOfArgs = "<< numOfArgs <<std::endl;
            i+= 1;

            if(numOfArgs > 0) {
                for(int j = 0; j <  numOfArgs; j++) {
                    if(j == 0) arg1 = this->fileContents[j+i];
                    else {
                        arg2 = this->fileContents[j+i];
                    }
                }
                i+= numOfArgs;
            }
            
            // std::cout << "i HERE = "<< i <<std::endl;
        }
        // std::cout << "instruction = "<< instruction <<std::endl;
        // std::cout << "arg1 = "<< arg1 <<std::endl;
        // std::cout << "arg2 = "<< arg2 <<std::endl;
        // std::cout << "i = "<< i <<std::endl;
        
        this->fileLines[pc] = make_tuple(
            pc,
            instruction,
            arg1,
            arg2
        );
        // this->printTuple(
        //     pc,
        //     instruction,
        //     arg1,
        //     arg2
        // );
        pc = i;
        
        // std::cout << "pc = "<< pc <<std::endl;
    }
}

void Simulator::printTuple(
    uint16_t pc,
    std::string instruction,
    std::string arg1,
    std::string arg2
) {
    std::cout << "map[" << pc << "] : "
    << instruction << " " 
    << arg1 << " " 
    << arg2 << " "    
    <<std::endl;
}


void Simulator::printFileLines() {
    FileLines::iterator it = this->fileLines.begin();
    uint16_t pc = 0;
    std::string instruction = "";
    std::string arg1 = "";
    std::string arg2 = "";
    do {
        uint16_t key = it->first;
        AddressOpcodeArgsLine currentLine = it->second;
        pc = std::get<0>(currentLine);
        instruction = std::get<1>(currentLine);
        arg1 = std::get<2>(currentLine);
        arg2 = std::get<3>(currentLine);
        this->printTuple(
            pc,
            instruction,
            arg1,
            arg2
        );
        it++;
    } while(it != this->fileLines.end());
}