#include <args.h>
#include <fstream>
#include <iostream>
#include <string>

Args::~Args(){}
Args::Args(){}

std::string Args::getFileName() {
    return this->fileName;
}

void Args::checkArgsForErrors(std::fstream *source, int argc, char ** argv) {
    if(argc == NULL) throw "nullPointer";
    std::fstream* sourceCodeContains = source;
    std::string error = "";
    if (argc != this->argumentsExpected)
    {
        error = "Arguments non compliant, requires one argument, file name as in '[executablepath] filename.asm'";
        throw error;
    } else
    {
        std::string fileName(argv[1]);
        this->fileName = fileName; 
        if (fileName.substr(fileName.find_last_of(".") + 1) != "asm")
        {
            error = "Only accepts .asm files.";
            throw error;
        } else
        {       
            (*(sourceCodeContains)).open(argv[1],std::ios::in);
            if ((*(sourceCodeContains)).good())
            {
                std::cout<<"File '"<< argv[1]<<"' opened successfully."<<std::endl;
            }else
            {
                error = "File not found.";
                throw error;
            }   
        }
    }
}