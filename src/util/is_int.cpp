#include "is_int.hpp"

namespace util {
bool is_number(std::string value) {
    for (char c : value) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}
} // namespace util