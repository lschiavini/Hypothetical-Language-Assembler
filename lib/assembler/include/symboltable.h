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
typedef std::vector< uint16_t> ListOfUInts;

#define ADDRESSPOS 0
#define ISDEFINEDPOS 1
#define LISTOFUSEPOS 2 

#define DESIRED_ADDRESS 0
#define ADDRESS_KEY 1



typedef std::tuple<uint16_t, uint16_t> DesiredAddressToKeyAddress;
typedef std::vector<DesiredAddressToKeyAddress> ListOfUsedLabel;
// <address, isDefined, listOfUse>
typedef std::tuple< uint16_t, bool, ListOfUsedLabel > Row;

// <label, row>
typedef std::map<std::string, Row> Table;


class SymbolTable {
    private:
      void MOCKSymbolTable();
      ListOfUsedLabel appendToUsedList(ListOfUsedLabel usedList, ListOfUsedLabel newUsedItems);
      void updatesListOfUse(
          std::string label,
          uint16_t definitionAddress,
          bool isDefinition,
          ListOfUsedLabel listOfUseItems 
      );
    public:
        Table table;
        ~SymbolTable();
        SymbolTable();
        ListOfUInts fromListOfLabelToUints(ListOfUsedLabel listOfUseLABEL);        
        void printTable();
        void printRow(std::string label, Row row);
        bool contains(std::string label);
        Table::iterator getTablePosition(std::string label);
        void adds(
            std::string label,
            uint16_t address, 
            bool isDefinition, 
            ListOfUsedLabel newListOfUse,
            bool isCONSTVal = false
          );
        bool isDefined(std::string label);
        uint16_t getsAddressValue(std::string label);
        ListOfUsedLabel getsUsedPositions(std::string label);
};

#endif