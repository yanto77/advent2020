#pragma once
#include <iostream>
#include "vector_helpers.h"

#define COLOR_BLACK()   "\033[30m"
#define COLOR_RED()     "\033[31m"
#define COLOR_GREEN()   "\033[32m"
#define COLOR_YELLOW()  "\033[33m"
#define COLOR_BLUE()    "\033[34m"
#define COLOR_MAGENTA() "\033[35m"
#define COLOR_CYAN()    "\033[36m"
#define COLOR_WHITE()   "\033[37m"
#define COLOR_GRAY()    "\033[38m"
#define COLOR_RESET()   "\033[39m"


template <typename T>
void print_col(const std::vector<T>& input)
{
    for (const auto& d : input)
    {
        std::cout << "  " << static_cast<int>(d) << '\n';
    }
}

template <typename T>
void print_row(const std::vector<T>& input)
{
    for (const auto& d : input)
    {
        std::cout << "  " << static_cast<int>(d) << ", ";
    }
    std::cout << '\n';
}

template <typename T>
void print_row(const std::vector<vec2<T>>& input)
{
    for (const auto& vec : input)
    {
        std::cout << "  (" << vec.x << ", " << vec.y << "), ";
    }
    std::cout << '\n';
}

inline void print_bits(uint8_t trg, bool color = false)
{
    for (int i = 64; i > 8; --i)
    {
        if (color)
            printf(get_bit(trg, i) ? COLOR_GREEN() "1" : COLOR_CYAN() "0");
        else
            printf(get_bit(trg, i) ? "1" : "0");
        printf(COLOR_RESET());
    }
}

inline void print_bits(uint64_t trg, bool color = false)
{
    for (int i = 64; i > 0; --i)
    {
        if (color)
            printf(get_bit(trg, i) ? COLOR_GREEN() "1" : COLOR_CYAN() "0");
        else
            printf(get_bit(trg, i) ? "1" : "0");
        printf(COLOR_RESET());
    }
}
