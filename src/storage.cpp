#include "storage.h"

void Storage::set(const std::string& key, const std::string& value) {
    data_[key] = value ; 
}

std::optional<std::string> Storage::get(const std::string& key) const {
    auto it = data_.find(key);
    if(it == data_.end()){
        return std::nullopt;
    }
    return it->second ;
}

bool Storage::remove(const std::string& key){
    if (data_.erase(key) > 0) {
        return true;
    }
    return false;
}

bool Storage::exists(const std::string& key) const{
    if(data_.count(key)){
        return true;
    }
    return false ;
}