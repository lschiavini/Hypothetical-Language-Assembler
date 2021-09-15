#include <iostream>
#include <fstream>
#include <args.h>
#include <utils.h>
#include <assembler.h>
#include <simulator.h>

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

    // if(myAssembler.canSimulate || true) {
    // Simulator mySim(fileName);
    // mySim.simulate();
    // }

    std::cout << "End of Show"<< std::endl;
    return 0;
}