#include <iostream>
#include <ostream>
#include <string>
#include <unordered_set>
#include <bitset>
#include <cstdint>

#define test_iter(x) test_func_iter(x, #x)
#define test_normal(x) test_func(x, #x)

std::string unique_sorted{"abcdefg"};
std::string unique{"badcfehg"};
std::string not_unique{"bbaaccdd"};
std::string not_unique_one_char{"bacdeef"};

template <typename Iter>
bool is_unique_with_brute_force(Iter begin, Iter end) {
    for(; begin != end; ++begin) {
        for(auto iter = begin + 1; iter != end; ++iter) {
            if(*iter == *begin) {
                return false;
            }
        }
    }
    return true;
}

template <typename Iter>
bool is_unique_alg_with_hash_table(Iter begin, Iter end) {
    std::unordered_set<typename Iter::value_type> temp{};
    for(; begin != end; ++begin) {
        if(temp.contains(*begin)) {
            return false;
        }
        temp.insert(*begin);
    }
    return true;
}

bool is_unique_string_with_bit_manip_with_bitset(std::string_view str) {
    std::bitset<26> bits{};
    // Assume all lowercase
    for(auto character : str) {
        auto value = character - 'a';
        if(bits.test(value)) return false;

        bits.set(value);
    }
    return true;
}

bool is_unique_string_with_bit_manip_with_four_byte_int(std::string_view str) {
    std::uint32_t temp{};
    // Assume all lowercase
    for(auto character : str) {
        auto value = character - 'a';
        if(temp & (1 << value)) return false;

        temp |= (1 << value);
    }
    return true;
}

template <typename Func>
void test_func_iter(Func func, std::string_view func_name,std::ostream& os = std::cout) {
    os << func_name << ": "
        << func(unique_sorted.begin(), unique_sorted.end())
        << func(unique.begin(), unique.end())
        << func(not_unique.begin(), not_unique.end())
        << func(not_unique_one_char.begin(), not_unique_one_char.end()) << '\n';
}

template <typename Func>
void test_func(Func func, std::string_view func_name,std::ostream& os = std::cout) {
    os << func_name << ": "
        << func(unique_sorted)
        << func(unique)
        << func(not_unique)
        << func(not_unique_one_char) << '\n';
}

int main() {
    test_iter(is_unique_with_brute_force<std::string::iterator>);
    test_iter(is_unique_alg_with_hash_table<std::string::iterator>);
    test_normal(is_unique_string_with_bit_manip_with_bitset);
    test_normal(is_unique_string_with_bit_manip_with_four_byte_int);
}