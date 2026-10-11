#include "command_registry.h"
#include "commands.h"

CommandRegistry::CommandRegistry() {
    commands_["SET"] = std::make_unique<SetCommand>();
    commands_["GET"] = std::make_unique<GetCommand>();
    commands_["DEL"] = std::make_unique<DelCommand>();
}

Command* CommandRegistry::find(const std::string& name) const {
    auto it = commands_.find(name);
    if (it == commands_.end()) {
        return nullptr;
    }
    return it->second.get();
}