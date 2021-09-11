#include <args.h>
#include <fstream>
#include <iostream>
#include <string>

class Args {
    public:
        Args::~Args(){}
        Args::Args(){}

        void checkArgsForErrors(std::fstream * sourceCode, int argc, char ** argv) {
            std::fstream sourceCodeContains = *(sourceCode);
            std::string error = "";
            if (argc!=2)
            {
                error = "Arguments number is not valid, this program recieves the name of file to be assembled as an argument.";
                throw error;
            } else
            {
                std::string name(argv[1]);

                if (name.substr(name.find_last_of(".") + 1) != "asm")
                {
                    error = "File extension is not valid, only accepts .asm files.";
                    throw error;
                } else
                {       
                    sourceCodeContains.open(argv[1],std::ios::in);
                    if (sourceCodeContains.good())
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
};