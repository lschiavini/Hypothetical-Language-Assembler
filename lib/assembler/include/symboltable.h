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
    private:
      void MOCKSymbolTable();
      void printTable();
      Table::iterator getPositions(std::string label);
      std::string getListAsString(ListOfStrings vectorList);
    public:
        Table table;
        ~SymbolTable();
        SymbolTable();
        bool contains(std::string label);
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