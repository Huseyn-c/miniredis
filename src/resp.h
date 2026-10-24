#pragma once
#include <string>
#include <vector>
#include "response.h"

std::string serialize(const Response& r);

bool parseRESP(const std::string& buffer, std::vector<std::string>& args,size_t& consumed);