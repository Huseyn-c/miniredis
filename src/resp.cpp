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

static bool readNumber(const std::string& buffer, size_t& pos, int& out) {
    size_t end = buffer.find("\r\n", pos);
    if (end == std::string::npos) {
        return false;
    }
    size_t start = pos + 1;
    size_t length = end - pos - 1;
    std::string num = buffer.substr(start, length);
    out = std::stoi(num);
    pos = end + 2;
    return true;
}

bool parseRESP(const std::string& buffer, std::vector<std::string>& args, size_t& consumed) {
    args.clear();
    size_t pos = 0;
    if (buffer.empty() || buffer[0] != '*') {
        return false;
    }
    int count = 0;
    if (!readNumber(buffer, pos, count)) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        if (pos >= buffer.size() || buffer[pos] != '$') {
            return false;
        }
        int len = 0;
        if (!readNumber(buffer, pos, len)) {
            return false;
        }
        if (pos + len + 2 > buffer.size()) {
            return false;
        }
        args.push_back(buffer.substr(pos, len));
        pos += len + 2;
    }
    consumed = pos;
    return true;
}