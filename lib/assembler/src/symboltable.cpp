#include <symboltable.h>
#include <stringUtils.h>

SymbolTable::~SymbolTable(){}

SymbolTable::SymbolTable(){
    // this->MOCKSymbolTable();
    // this->printTable();
    std::cout << "Symbol Table set"<< std::endl;
}

void SymbolTable::MOCKSymbolTable() {
    ListOfStrings list;
    //Adds first row
    list.insert(list.begin(), {"7", "9"});
    this->adds("OLD_DATA", "2", true, list);

    // erases list
    list.erase(list.begin());
    list.erase(list.begin());

    // adds second row
    list.insert(list.begin(), {"11", "15"});
    this->adds("DOIS", "0", true, list);

    // erases list
    list.erase(list.begin());
    list.erase(list.begin());

    //Adds another element of usedList on first row
    list.insert(list.begin(), {"19"});
    this->adds("OLD_DATA", "2", true, list);

}

void SymbolTable::printTable() {
    Table::iterator iteratorMap;
    std::string label;
    Row row;
    std::string value;
    bool isDefined;
    ListOfStrings listOfUse;
    std::string fullListOfUse;
    std::cout << "_____________________"<<std::endl;
    for(
        iteratorMap = this->table.begin(); 
        iteratorMap != this->table.end(); 
        ++iteratorMap 
    )
    {
        label = iteratorMap->first;
        row = iteratorMap->second;
        value = std::get<0>(row);
        isDefined = std::get<1>(row);
        listOfUse = std::get<2>(row);
        fullListOfUse = getListAsString(listOfUse);

        std::cout << label << "\t\t| Address = " << 
            value << "\t| isDefined = "<< isDefined
            << "\t| listOfUse = "<< fullListOfUse <<  
            std::endl;
    } 
    std::cout << "_____________________"<<std::endl;
}

Table::iterator SymbolTable::getTablePosition(std::string label) {
    Table::iterator mapEnd = this->table.end();
    Table::iterator position;      
    position = this->table.find(label);
    return position;
}

bool SymbolTable::contains(std::string label){
    ListOfStrings listOfUseItems = std::get<LISTOFUSEPOS>(this->table[label]);
    bool isDefined = std::get<ISDEFINEDPOS>(this->table[label]);
    if(!listOfUseItems.empty() || isDefined) {
        // std::cout << "PASSO '1': \t  contains position" << std::endl;
        return true;
    }
    // std::cout << "PASSO 1: \t NOT contains position" << std::endl;
    return false;
}

ListOfStrings SymbolTable::appendToUsedList(ListOfStrings usedList, ListOfStrings newUsedItems) {
    for (int i=0; i < newUsedItems.size(); i++ ) {
        usedList.push_back(newUsedItems[i]);
    }
    return usedList;
}

void SymbolTable::updatesListOfUse(
    std::string label,
     std::string value,
     bool isDefined,
     ListOfStrings listOfUseItems 
) {
    Row rowToBeInserted;
    Row previousRow = this->table[label];
    ListOfStrings oldListOfUse = std::get<2>(previousRow);
    ListOfStrings newListOfUse;
    newListOfUse = this->appendToUsedList(oldListOfUse, listOfUseItems);
    rowToBeInserted = make_tuple(value, isDefined, newListOfUse);
    this->table[label] = rowToBeInserted;
}


void SymbolTable::adds(
    std::string label,
    std::string address, 
    bool isDefined, 
    ListOfStrings listOfUseItems
){
    Row rowToBeInserted;
    if(label != "") {
        if(this->contains(label)) {
            this->updatesListOfUse(label, address, isDefined, listOfUseItems);
        } else {
            rowToBeInserted = make_tuple(address, isDefined, listOfUseItems);
            std::pair<std::string, Row> labelAndContents(label, rowToBeInserted);
            this->table[label] = rowToBeInserted;
        }  
        // this->printTable();
    }
}

bool SymbolTable::isDefined(std::string label){
    Row currentRow = this->table[label];
    bool isDefinedValue = std::get<1>(currentRow);
    return isDefinedValue;
}

std::string SymbolTable::getsAddressValue(std::string label){
    Row currentRow = this->table[label];
    std::string addressValue = std::get<0>(currentRow);
    return addressValue;
}


ListOfStrings SymbolTable::getsUsedPositions(std::string label){
    Row currentRow = this->table[label];
    ListOfStrings usedPositions = std::get<2>(currentRow);
    return usedPositions;
}