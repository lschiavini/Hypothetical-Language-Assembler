#pragma once
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <fstream>
#include <stringUtils.h>


typedef std::vector< std::string> ListOfStrings;

class Simulator {
    public:
        Simulator(std::string fileName);
        ~Simulator();
        void simulate();

    private:
        std::string fileContentsStrint;
        ListOfStrings fileContents;
        std::string fileName;
        std::string fileDir;
        std::fstream input;
        void setFileContents();

};

#endif