#include "parser.h"
#include <sstream>

std::vector<std::string> tokenize(const std::string& line){
    std::vector<std::string> result;
    std::istringstream in(line);
    std::string word;
    while(in >> word){
        result.push_back(word);
    }
    return result ; 
}