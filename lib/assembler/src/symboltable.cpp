#include <symboltable.h>

SymbolTable::~SymbolTable(){}
SymbolTable::SymbolTable(){
    std::cout << "Symbol Table set"<< std::endl;


}

void SymbolTable::printTable() {
    Table::iterator iteratorMap;

    std::cout << "_____________________"<<std::endl;
    for(
        iteratorMap = this->table.begin(); 
        iteratorMap != this->table.end(); 
        ++iteratorMap 
    )
    {
        std::string label = iteratorMap->first;
        Row row = iteratorMap->second;
        std::uint16_t value = std::get<0>(row);
        bool isDefined = std::get<1>(row);
        ListOfStrings listOfUse = std::get<2>(row);
        std::cout << label << " = " << 
            value << "| isDefined = "<< isDefined
            << "| listOfUse = "<< listOfUse.at(0) <<  
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

void SymbolTable::adds(
    std::string label,
    uint16_t value, 
    bool isDefined, 
    ListOfStrings listOfUse
){
    Table::iterator position = this->table.begin();
    
    if(this->contains(label)) {
        position = this->getPositions(label);
    } 

    Row rowToBeInserted = make_tuple(value, isDefined, listOfUse);
    this->table.insert(std::pair<std::string, Row>(label ,rowToBeInserted));
}
bool SymbolTable::isDefined(std::string label){
    return false; // TODO isDefined
}
bool SymbolTable::isDefinition(std::string label){
    return false; // TODO isDefinition
}
std::string SymbolTable::getsAddressValue(std::string label){
    return "fakeAddress"; // TODO getsAddressValue
}