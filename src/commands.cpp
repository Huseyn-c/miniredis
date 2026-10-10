#include "commands.h"

Response SetCommand::execute(Storage& storage, const std::vector<std::string>& args) {
    if (args.size() != 3) {
        return Response::error("ERR wrong number of arguments for 'set' command");
    }
    storage.set(args[1], args[2]);
    return Response::ok();
}

Response GetCommand::execute(Storage& storage, const std::vector<std::string>& args){
    if (args.size() != 2) {
        return Response::error("ERR wrong number of arguments for 'get' command");
    }
    auto v = storage.get(args[1]);
    if(v == std::nullopt){
        return Response::nil();
    }
    else {
        return Response::bulk(*v);
    }
}

Response DelCommand::execute(Storage& storage, const std::vector<std::string>& args){
    if (args.size() < 2) {
        return Response::error("ERR wrong number of arguments for 'del' command");
    }
    size_t count = 0 ; 
    for(size_t i = 1 ; i < args.size(); i++){
        if(storage.remove(args[i])){
            count++;
        }
    }
    return Response::integer(count);
}
