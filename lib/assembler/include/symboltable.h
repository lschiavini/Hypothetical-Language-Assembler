  // Symbol Table
#pragma once
#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <string>
  
typedef std::vector< std::string> ListOfStrings;

// <value, isDefined, listOfUse>
typedef std::tuple< uint16_t, bool, ListOfStrings > Row;

// <label, row>
typedef std::map<std::string, Row> Table;

class SymbolTable {
    public:
        Table table;
        ~SymbolTable();
        SymbolTable();
        void printTable();
        bool contains(std::string label);
        Table::iterator getPositions(std::string label);
        void adds(
            std::string label,
            uint16_t value, 
            bool isDefined, 
            ListOfStrings listOfUse);
        bool isDefined(std::string label);
        bool isDefinition(std::string label);
        std::string getsAddressValue(std::string label);
};

#endif