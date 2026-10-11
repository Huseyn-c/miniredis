#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "command.h"

class CommandRegistry {
public:
    CommandRegistry();
    Command* find(const std::string& name) const;

private:
    std::unordered_map<std::string, std::unique_ptr<Command>> commands_;
};