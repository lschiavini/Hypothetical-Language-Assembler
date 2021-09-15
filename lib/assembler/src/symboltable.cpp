#include <symboltable.h>
#include <stringUtils.h>

SymbolTable::~SymbolTable(){}

SymbolTable::SymbolTable(){
    // this->MOCKSymbolTable();
    // this->printTable();
    std::cout << "Symbol Table set"<< std::endl;
}

void SymbolTable::MOCKSymbolTable() {
    ListOfUsedLabel list;
    //Adds first row
    list.insert(list.begin(), {7, 9});
    this->adds("OLD_DATA", 2, true, list);

    // erases list
    list.erase(list.begin());
    list.erase(list.begin());

    // adds second row
    list.insert(list.begin(), {11, 15});
    this->adds("DOIS", 0, true, list);

    // erases list
    list.erase(list.begin());
    list.erase(list.begin());

    //Adds another element of usedList on first row
    list.insert(list.begin(), {19, 12});
    this->adds("OLD_DATA", 2, true, list);

}

ListOfUInts SymbolTable::fromListOfLabelToUints(ListOfUsedLabel listOfUseLABEL) {
    ListOfUInts listOfUseUINTs(listOfUseLABEL.size());
    for(uint16_t i = 0; i < listOfUseLABEL.size();  i++){
        DesiredAddressToKeyAddress currentAddresses = listOfUseLABEL[i];
        listOfUseUINTs[i] = std::get<DESIRED_ADDRESS>(currentAddresses);
    }
    return listOfUseUINTs;
}

void SymbolTable::printRow(std::string label, Row row) {

    uint16_t value = std::get<ADDRESSPOS>(row);
    bool isDefined = std::get<ISDEFINEDPOS>(row);
    ListOfUsedLabel listOfUseLABEL = std::get<LISTOFUSEPOS>(row);
    ListOfUInts listOfUseSTRING = this->fromListOfLabelToUints(listOfUseLABEL);
    std::string fullListOfUse = getListAsStringUint(listOfUseSTRING);

    // if(!removeAllSpaces(std::to_string(value)).empty()) {
        std::cout << label << "\t\t| Address = " << 
        value << "\t| isDefined = "<< isDefined
        << "\t| listOfUse = "<< fullListOfUse <<  
        std::endl;
    // }
}

void SymbolTable::printTable() {
    Table::iterator iteratorMap;
    std::string label;
    Row row;
    
    std::cout << "__________________________________________SYMBOL TABLE__________________________________________"<<std::endl;
    for(
        iteratorMap = this->table.begin(); 
        iteratorMap != this->table.end(); 
        ++iteratorMap 
    )
    {
        label = iteratorMap->first;
        row = iteratorMap->second;
        this->printRow(label, row);
    } 
    std::cout << "________________________________________________________________________________________________"<<std::endl;
}

Table::iterator SymbolTable::getTablePosition(std::string label) {
    Table::iterator position;      
    position = this->table.find(label);
    return position;
}

bool SymbolTable::contains(std::string label){
    ListOfUsedLabel listOfUseItems = std::get<LISTOFUSEPOS>(this->table[label]);
    bool isDefined = std::get<ISDEFINEDPOS>(this->table[label]);
    if(!listOfUseItems.empty() || isDefined) {
        return true;
    }
    return false;
}

ListOfUsedLabel SymbolTable::appendToUsedList(ListOfUsedLabel usedList, ListOfUsedLabel newUsedItems) {
    for (int i=0; i < newUsedItems.size(); i++ ) {
        usedList.push_back(newUsedItems[i]);
    }
    return usedList;
}

void SymbolTable::updatesListOfUse(
    std::string label,
     uint16_t definitionAddress,
     bool isDefinition,
     ListOfUsedLabel listOfUseItems 
) {
    Row rowToBeInserted;
    Row previousRow = this->table[label];
    uint16_t addressToUse = std::get<ADDRESSPOS>(this->table[label]);
    if(isDefinition) addressToUse = definitionAddress;

    ListOfUsedLabel oldListOfUse = std::get<LISTOFUSEPOS>(previousRow);
    bool oldIsDefined = std::get<ISDEFINEDPOS>(previousRow);
    ListOfUsedLabel newListOfUse;
    newListOfUse = this->appendToUsedList(oldListOfUse, listOfUseItems);
    
    rowToBeInserted = make_tuple(addressToUse, isDefinition || oldIsDefined, newListOfUse);
    this->table[label] = rowToBeInserted;
}

void SymbolTable::adds(
    std::string label,
    uint16_t address, 
    bool isDefinition, 
    ListOfUsedLabel listOfUseItems,
    bool isCONSTVal
){
    if(isCONSTVal) return;
    Row rowToBeInserted;
    ListOfUsedLabel emptyList, listToInsert;
    if(isDefinition) {
        listToInsert = emptyList;
    } else listToInsert = listOfUseItems;

    if(!removeAllSpaces(label).empty()) {
        if(this->contains(label)) {
            bool setIsDefined = this->isDefined(label);
            this->updatesListOfUse(label, address, isDefinition, listToInsert);
        } else {
            rowToBeInserted = make_tuple(address, isDefinition, listToInsert);
            std::pair<std::string, Row> labelAndContents(label, rowToBeInserted);
            this->table[label] = rowToBeInserted;
            // this->printRow(label, rowToBeInserted);
        }
    }
}

bool SymbolTable::isDefined(std::string label){
    Row currentRow = this->table[label];
    bool isDefinedValue = std::get<ISDEFINEDPOS>(currentRow);
    return isDefinedValue;
}

uint16_t SymbolTable::getsAddressValue(std::string label){
    Row currentRow = this->table[label];
    uint16_t addressValue = std::get<ADDRESSPOS>(currentRow);
    return addressValue;
}

ListOfUsedLabel SymbolTable::getsUsedPositions(std::string label){
    Row currentRow = this->table[label];
    ListOfUsedLabel usedPositions = std::get<LISTOFUSEPOS>(currentRow);
    return usedPositions;
}