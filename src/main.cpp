#include <iostream>
#include <fstream>
#include <args.h>

int main(int argc, char ** argv)
{
    Args myArgs;
    std::fstream sourceCode;
    try {
        myArgs.checkArgsForErrors(&sourceCode, argc, argv);
    } catch(std::string error) {
        std::cout << error << std::endl;
    }
    
    std::cout << "Hello World!";
    return 0;
}