#pragma once
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <fstream>
#include <iostream>
#include <map>

class Assembler {
    public:
        Assembler(std::fstream *source);
        ~Assembler();
        void assembleFile();
    private:
        std::fstream * sourceCode;
        std::fstream * assemblingCode;
        std::fstream * assembledCode;
        std::string fileName = "binComments.asm";


        void onePassAlgorithm();
        void removeComments();
        void writeAssembledFile();
        void getTokens();
        void getOpcode();
        void getAddress();
        void setAddress();

    
};

#endif