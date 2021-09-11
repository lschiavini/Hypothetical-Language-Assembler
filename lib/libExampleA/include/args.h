#ifndef ARGS_H
#define ARGS_H

#include <fstream>

class Args {
    public:
        Args();
        void checkArgsForErrors(std::fstream * sourceCode, int argc, char ** argv);
        ~Args();
};

#endif