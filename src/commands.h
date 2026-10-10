#pragma once
#include "command.h"

class SetCommand : public Command {
public:
    Response execute(Storage& storage, const std::vector<std::string>& args) override;
};

class GetCommand : public Command {
public:
    Response execute(Storage& storage, const std::vector<std::string>& args) override;
};

class DelCommand : public Command {
public:
    Response execute(Storage& storage, const std::vector<std::string>& args) override;
};