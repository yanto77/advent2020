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
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <x86intrin.h>

#ifdef NDEBUG
    #undef NDEBUG
    #include <cassert>
    #define NDEBUG 1
#else
    #include <cassert>
#endif

#include "helpers/bit_helpers.h"
#include "helpers/conv_helpers.h"
#include "helpers/hash_helpers.h"
#include "helpers/input_helpers.h"
#include "helpers/print_helpers.h"
#include "helpers/string_helpers.h"
#include "helpers/vec2.h"
#include "helpers/vec3.h"
#include "helpers/pow_helpers.h"
#include "helpers/parse_helpers.h"
#include "helpers/array_helpers.h"

#include "setup/days.h"
