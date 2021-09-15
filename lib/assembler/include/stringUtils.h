#pragma once
#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include<iostream>

typedef std::vector< std::string> ListOfStrings;

template <typename Out>

void split(const std::string &s, char delim, Out result);
std::vector<std::string> split(const std::string &s, char delim);
std::string getListAsString(ListOfStrings vectorList);
std::string removeMultipleSpaces(std::string inputString);
std::string removeAllSpaces(std::string inputString);
std::string trimFirstAndLastWhiteSpace(std::string stringInput);
bool isNumber(std::string stringToTest);

#endif