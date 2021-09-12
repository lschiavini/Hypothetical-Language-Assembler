#include <iostream>
#include <fstream>
#include <args.h>
#include <utils.h>
#include <assembler.h>

int main(int argc, char ** argv)
{
    Args myArgs;
    std::fstream sourceCode;
    try {
        myArgs.checkArgsForErrors(&sourceCode, argc, argv);
    } catch(std::string error) {
        std::cout << error << std::endl;
    }

    printFile(&sourceCode);
    Assembler myAssembler;

    

    std::cout << "End of Show"<< std::endl;
    return 0;
}