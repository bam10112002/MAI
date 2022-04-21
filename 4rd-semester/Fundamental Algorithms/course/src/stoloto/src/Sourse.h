#ifndef SOURSE_H
#define SOURSE_H

#include <iostream>
#include <string>
#include <map>
#include <random>
#include <vector>
#include <list>
#include <fstream>
#include <ctime>
#include <cmath>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdint>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <algorithm>
#include "../../json/single_include/nlohmann/json.hpp"

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using json = nlohmann::json;

// std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());


void generateNum(const int border, std::vector<int> & vec);

#endif