#include <symboltable.h>

SymbolTable::~SymbolTable(){}
SymbolTable::SymbolTable(){
    this->MOCKSymbolTable();
    this->printTable();
    std::cout << "Symbol Table set"<< std::endl;
}

void SymbolTable::MOCKSymbolTable() {
    ListOfStrings list;
    //Adds first row
    list.insert(list.begin(), {"7", "9"});
    this->adds("OLD_DATA", 2, true, list);

    // erases list
    list.erase(list.begin());
    list.erase(list.begin());

    // adds second row
    list.insert(list.begin(), {"11", "15"});
    this->adds("DOIS", 0, true, list);

    // erases list
    list.erase(list.begin());
    list.erase(list.begin());

    //Adds another element of usedList on first row
    list.insert(list.begin(), {"19"});
    this->adds("OLD_DATA", 2, true, list);

}

std::string SymbolTable::getListAsString(ListOfStrings vectorList) {
    std::string listAsString;
    for (uint16_t i=0; i < vectorList.size(); i++) {
        if(i==0) {
            listAsString.append(("%d " , vectorList.at(i)));
        } else{
            listAsString.append(" -> ");
            listAsString.append(("%d" , vectorList.at(i)));
        }
    }
    return listAsString; 
}

void SymbolTable::printTable() {
    Table::iterator iteratorMap;
    std::string label;
    Row row;
    std::uint16_t value;
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

bool SymbolTable::contains(std::string label){
    Table::iterator mapEnd = this->table.end();
    Table::iterator position;
    position = this->table.find(label);
    if(position == mapEnd) {
        return false;
    }
    return true;
}

Table::iterator SymbolTable::getPositions(std::string label) {
    Table::iterator position = this->table.begin(); // TODO getPositions
    return position;
}

ListOfStrings SymbolTable::appendToUsedList(ListOfStrings usedList, ListOfStrings newUsedItems) {
    for (int i=0; i < newUsedItems.size(); i++ ) {
        usedList.push_back(newUsedItems[i]);
    }
    return usedList;
}

void SymbolTable::updatesListOfUse(
    std::string label,
     uint16_t value,
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
    uint16_t value, 
    bool isDefined, 
    ListOfStrings listOfUseItems
){
    Table::iterator position = this->table.begin();
    Row rowToBeInserted;
    if(this->contains(label)) {
        this->updatesListOfUse(label, value, isDefined, listOfUseItems);
    } else {
        rowToBeInserted = make_tuple(value, isDefined, listOfUseItems);
        std::pair<std::string, Row> labelAndContents(label, rowToBeInserted);
        this->table.insert(position, labelAndContents);  
    }   
}

bool SymbolTable::isDefined(std::string label){
    Row currentRow = this->table[label];
    return false; // TODO isDefined
}

bool SymbolTable::isDefinition(std::string label){
    return false; // TODO isDefinition
}

std::string SymbolTable::getsAddressValue(std::string label){
    return "fakeAddress"; // TODO getsAddressValue
}