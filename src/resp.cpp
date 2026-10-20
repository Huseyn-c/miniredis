#include "response.h"
#include "resp.h"

std::string serialize(const Response& r){
    switch (r.type) {
        case Response::Type::SimpleString:
            return "+" + r.text + "\r\n";
        case Response::Type::BulkString:
            return "$" + std::to_string(r.text.size()) + "\r\n" + r.text + "\r\n";
        case Response::Type::Nil:
            return "$-1\r\n";
        case Response::Type::Integer:
            return ":" + std::to_string(r.number) + "\r\n";
        case Response::Type::Error:
            return "-" + r.text + "\r\n";
    }
    return "";
}