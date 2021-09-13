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
      std::string getListAsString(ListOfStrings vectorList);
      ListOfStrings appendToUsedList(ListOfStrings usedList, ListOfStrings newUsedItems);
      void updatesListOfUse(
          std::string label,
          uint16_t value,
          bool isDefined,
          ListOfStrings listOfUseItems 
      );
    public:
        Table table;
        ~SymbolTable();
        SymbolTable();
        bool contains(std::string label);
        void adds(
            std::string label,
            uint16_t value, 
            bool isDefined, 
            ListOfStrings newListOfUse);
        bool isDefined(std::string label);
        std::uint16_t getsAddressValue(std::string label);
        ListOfStrings getsUsedPositions(std::string label);
};

#endif