#include <iostream>
#include <fstream>
#include <args.h>
#include <utils.h>
#include <assembler.h>

int main(int argc, char ** argv)
{
    Args myArgs;
    std::string fileName;
    std::fstream sourceCode, assembledCode;
    try {
        myArgs.checkArgsForErrors(&sourceCode, argc, argv);
    } catch(std::string error) {
        std::cout << error << std::endl;
    }
    fileName = myArgs.getFileName();

    // printFile(&sourceCode);

    Assembler myAssembler(&sourceCode, fileName);
    myAssembler.assembleFile();

    printFile(&assembledCode);

    std::cout << "End of Show"<< std::endl;
    return 0;
}