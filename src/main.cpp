#include <iostream>
#include <fstream>
#include <args.h>

int main(int argc, char ** argv)
{
    std::fstream sourceCode;
    Args myArgs;

    myArgs.checkArgsForErrors(&sourceCode, argc, argv);

    std::cout << "Hello World!";
    return 0;
}