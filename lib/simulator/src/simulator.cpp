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

    for(int i = 0; i < this->fileContents.size() ; i++) {
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
        }
        else if(this->opcodeToInstruction.find(this->fileContents[i]) != this->opcodeToInstruction.end()) {
            instruction = this->opcodeToInstruction[this->fileContents[i]];
            // std::cout << "instruction = "<< instruction <<std::endl;
            uint16_t numOfArgs = this->instructToSizeInMemory[instruction] - 1;
            for(int j = 1; j <=  numOfArgs; j++) {
                if(j == 1) arg1 = this->fileContents[i + j];
                else {
                    arg2 = this->fileContents[i + j];
                }                
                std::cout << "j = "<< j <<std::endl;
            }
            i+= numOfArgs;
            // std::cout << "numOfArgs = "<< numOfArgs <<std::endl;
            // std::cout << "arg1 = "<< arg1 <<std::endl;
            // std::cout << "arg2 = "<< arg2 <<std::endl;
            // std::cout << "i = "<< i <<std::endl;
        }
        
        this->fileLines[pc] = make_tuple(
            pc,
            instruction,
            arg1,
            arg2
        );
        this->printTuple(
            pc,
            instruction,
            arg1,
            arg2
        );
        
        pc = i;
        
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
    while(it != this->fileLines.end()) {
        
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
    }
}