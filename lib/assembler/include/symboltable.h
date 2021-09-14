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

#define VALUEPOS 0
#define ISDEFINEDPOS 1
#define LISTOFUSEPOS 2  
// <address, isDefined, listOfUse>
typedef std::tuple< std::string, bool, ListOfStrings > Row;

// <label, row>
typedef std::map<std::string, Row> Table;

class SymbolTable {
    private:
      void MOCKSymbolTable();
      ListOfStrings appendToUsedList(ListOfStrings usedList, ListOfStrings newUsedItems);
      void updatesListOfUse(
          std::string label,
          std::string value,
          bool isDefined,
          ListOfStrings listOfUseItems 
      );
    public:
        Table table;
        ~SymbolTable();
        SymbolTable();
        void printTable();
        bool contains(std::string label);
        Table::iterator getTablePosition(std::string label);
        void adds(
            std::string label,
            std::string address, 
            bool isDefined, 
            ListOfStrings newListOfUse);
        bool isDefined(std::string label);
        std::string getsAddressValue(std::string label);
        ListOfStrings getsUsedPositions(std::string label);
};

#endif