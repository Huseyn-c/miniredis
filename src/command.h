#pragma once
#include <string>
#include <vector>
#include "storage.h"
#include "response.h"

class Command {
public:
    virtual ~Command() = default;
    virtual Response execute(Storage& storage, const std::vector<std::string>& args) = 0;
};