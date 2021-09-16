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

}

void Simulator::setFileContents() {
    std::string pathToFile = (this->fileDir + this->fileName);
    this->input.open(pathToFile, std::ios::in);
    std::cout << "\n\nSimulating with [" << pathToFile  << "]" <<std::endl;
    while(std::getline(this->input, this->fileContentsStrint));
    this->input.close();
    this->fileContents = split(this->fileContentsStrint, ' ');
    std::cout << "fileContents with [" << getListAsString(this->fileContents)  << "]" <<std::endl;
}
