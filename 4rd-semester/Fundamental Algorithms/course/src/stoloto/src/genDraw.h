#include <cstdint>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include "../../json/single_include/nlohmann/json.hpp"

using u8  = uint8_t;
using u64 = uint64_t;
using json = nlohmann::json;

std::string gendraw(const std::string sportloto);