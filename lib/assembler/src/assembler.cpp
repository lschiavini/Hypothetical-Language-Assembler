#include <assembler.h>
#include <fstream>
#include <iostream>
#include <string>

Assembler::~Assembler(){}
Assembler::Assembler(std::fstream *source){
    this->sourceCode = source;
    std::cout << "Assembler Set"<< std::endl;
}
void Assembler::onePassAlgorithm(){}


void Assembler::removeComments() {

}
void Assembler::writeAssembledFile() {
    std::string finalFileName = this->fileName.substr(0,this->fileName.find_last_of('.'))+".obj";;

    std::fstream output;
    output.open(finalFileName,std::ios::out );

    output.close();

    std::cout << "[check] .obj file written"<<std::endl;
}

void Assembler::assembleFile(){
    writeAssembledFile();
}


