#include <iostream>
#include <ostream>
#include <string_view>
#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>

#define test_normal(x) test_func(x, #x)

std::vector<std::pair<std::string, std::string>> test_data{
    {"taco cat", "atco cta"},
};

template <typename Func>
void test_func(Func func, std::string_view func_name,std::ostream& os = std::cout) {
    os << func_name << ": ";
    for(auto item : test_data) {
        os << func(item.first, item.second);
    }
    os << '\n';
}

// Assume m is longest substring
// Assume s is space count
// Time complexity: O(n + m * s)
// Space complexity: O(m)
bool check_permutation_palindrome(const std::string& original, const std::string& check_str) {
    if(original.size() != check_str.size()) return false;

    std::unordered_map<char, int> values{};

    for(int idx{}; idx < original.size(); ++idx) {
        if(original[idx] == ' ' && check_str[idx] == ' ') {
            for(const auto&[character, count]: values) {
                if(count) return false;
            }
            values.clear();
        }
        else {
            if(original[idx] == ' ' || check_str[idx] == ' ') return false;

            values[original[idx]]++;
            values[check_str[idx]]--;
        }
    }

    auto iter_begin_original{original.begin()}; 
    auto iter_rbegin_original{original.rbegin()};
    auto iter_begin_check_str{check_str.begin()}; 
    auto iter_rbegin_check_str{check_str.rbegin()};
    while(iter_begin_original != original.end() && iter_rbegin_original != original.rend()) {
        if((*iter_begin_original != *iter_rbegin_original) || (*iter_begin_check_str != *iter_rbegin_check_str)) return false;

        ++iter_begin_original;
        ++iter_rbegin_original;
        ++iter_begin_check_str;
        ++iter_rbegin_check_str;

        while(*iter_begin_original == ' ') {
            ++iter_begin_original;
            ++iter_begin_check_str;
        }
        while(*iter_rbegin_original == ' ') {
            ++iter_rbegin_original;
            ++iter_rbegin_check_str;
        }
    }
    return true;
}

int main() {
    test_normal(check_permutation_palindrome);
}