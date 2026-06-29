#include "is_int.hpp"
#include <cctype>

namespace util {
    bool is_number(std::string value) {
        for (char c : value) {
            if (!std::isdigit(c)) {
                return false;
            }
        }
        return true;
    }
}