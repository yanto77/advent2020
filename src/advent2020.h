#pragma once

#include <algorithm>
#include <array>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <set>
#include <string_view>
#include <string>
#include <unordered_map>
#include <vector>
#include <x86intrin.h>

#ifdef NDEBUG
#undef NDEBUG
#include <cassert>
#define NDEBUG
#else
#include <cassert>
#endif

struct input_t
{
    char* s;
    ssize_t len;
};

void day01(input_t);
void day02(input_t);
void day03(input_t);
void day04(input_t);
void day05(input_t);
void day06(input_t);
void day07(input_t);
void day08(input_t);
void day09(input_t);
void day10(input_t);
void day11(input_t);
void day12(input_t);
void day13(input_t);
void day14(input_t);
void day15(input_t);
void day16(input_t);
void day17(input_t);
void day18(input_t);
void day19(input_t);
void day20(input_t);
void day21(input_t);
void day22(input_t);
void day23(input_t);
void day24(input_t);
void day25(input_t);

// Helpers

void parse_input(const input_t& input, std::function<void(const std::string_view&)> line_cb);

int to_int(const std::string_view& sv);

char to_char(const std::string_view& sv);
