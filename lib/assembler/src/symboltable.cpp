#include <symboltable.h>

SymbolTable::~SymbolTable(){}
SymbolTable::SymbolTable(){
    std::cout << "Symbol Table set"<< std::endl;
}

void SymbolTable::printTable() {
    std::cout << "_____________________"<<std::endl;
    for(size_t i = 0; i != this->table.size(); i++ )
    {
        std::cout << std::get<0>(this->table[i]) << " = " << std::get<1>(this->table[i]) << std::endl;
    } 
    std::cout << "_____________________"<<std::endl;
}

bool SymbolTable::contains(std::string label){
    return false;
}

Table::iterator SymbolTable::getPositions(std::string label) {
    Table::iterator position = this->table.begin(); // TODO

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

    Row rowToBeInserted = make_tuple(label, value, isDefined, listOfUse);
    this->table.insert(position, rowToBeInserted);
}
bool SymbolTable::isDefined(std::string label){
    return false;
}
bool SymbolTable::isDefinition(std::string label){
    return false;
}
std::string SymbolTable::getsAddressValue(std::string label){
    return "fakeAddress"; // TODO
}