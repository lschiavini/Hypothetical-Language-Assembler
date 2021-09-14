#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <regex>
#include <stringUtils.h>

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::string getListAsString(ListOfStrings vectorList) {
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

std::string removeMultipleSpaces(std::string inputString) {
    std::regex multipleSpaces("\\s+");
    std::string str = std::regex_replace(inputString, multipleSpaces, std::string(" "));
    return str;
}
 

