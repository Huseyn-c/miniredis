#include <iostream>
#include <string>
#include "storage.h"
#include "command_registry.h"
#include "parser.h"

std::string formatResponse(const Response& r) {
    switch (r.type) {
        case Response::Type::SimpleString:
            return r.text;
        case Response::Type::BulkString:
            return "\"" + r.text + "\"";      
        case Response::Type::Nil:
            return "(nil)";
        case Response::Type::Integer:
             return "(integer) " + std::to_string(r.number); 
        case Response::Type::Error:
            return "(error) " + r.text; 
    }
    return "";
}

int main() {
    Storage storage;
    CommandRegistry registry;
    std::string line;

    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        auto tokens = tokenize(line);
        if (tokens.empty()) {
            std::cout << "> ";
            continue;
        }
        Command* cmd = registry.find(tokens[0]);
        Response r;
        if (cmd == nullptr) {
            r = Response::error("ERR unknown command '" + tokens[0] + "'");
        }
        else
        {
            r = cmd->execute(storage, tokens);
        }

        std::cout << formatResponse(r) << "\n";

        std::cout << "> ";
    }
    return 0;
}