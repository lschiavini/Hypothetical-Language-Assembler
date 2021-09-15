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

#define ADDRESSPOS 0
#define ISDEFINEDPOS 1
#define LISTOFUSEPOS 2 

#define DESIRED_ADDRESS 0
#define ADDRESS_KEY 1



typedef std::tuple<std::string, std::string> DesiredAddressToKeyAddress;
typedef std::vector<DesiredAddressToKeyAddress> ListOfUsedLabel;
// <address, isDefined, listOfUse>
typedef std::tuple< std::string, bool, ListOfUsedLabel > Row;

// <label, row>
typedef std::map<std::string, Row> Table;


class SymbolTable {
    private:
      void MOCKSymbolTable();
      ListOfUsedLabel appendToUsedList(ListOfUsedLabel usedList, ListOfUsedLabel newUsedItems);
      void updatesListOfUse(
          std::string label,
          std::string value,
          bool isDefinition,
          ListOfUsedLabel listOfUseItems 
      );
    public:
        Table table;
        ~SymbolTable();
        SymbolTable();
        ListOfStrings fromListOfLabelToStrings(ListOfUsedLabel listOfUseLABEL);        
        void printTable();
        void printRow(std::string label, Row row);
        bool contains(std::string label);
        Table::iterator getTablePosition(std::string label);
        void adds(
            std::string label,
            std::string address, 
            bool isDefinition, 
            ListOfUsedLabel newListOfUse,
            bool isCONSTVal = false
          );
        bool isDefined(std::string label);
        std::string getsAddressValue(std::string label);
        ListOfUsedLabel getsUsedPositions(std::string label);
};

#endif