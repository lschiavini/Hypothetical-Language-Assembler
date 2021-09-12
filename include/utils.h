
#pragma once
#ifndef UTILS_H
#define UTILS_H


#include <fstream>
#include <iostream>

void resetsReadAndWritePositions(std::fstream *sourceFile);
void printFile(std::fstream *source);

#endif