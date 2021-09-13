#pragma once
#ifndef ARGS_H
#define ARGS_H

#include <fstream>

class Args {
    public:
        int argumentsExpected = 2;
        std::string fileName;
        Args();
        void checkArgsForErrors(std::fstream *source, int argc, char ** argv);
        ~Args();
        std::string getFileName();
};

#endif