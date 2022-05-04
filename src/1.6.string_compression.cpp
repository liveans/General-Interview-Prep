#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>

#define test_normal(x) test_func(x, #x)

std::vector<std::string> test_data{
    "aabcccccaaa", // a2b1c5a3
    "abcd", // abcd
    "aabcd", // aabcd
};

template <typename Func>
void test_func(Func func, std::string_view func_name,std::ostream& os = std::cout) {
    os << func_name << ": ";
    for(auto item : test_data) {
        os << func(item) << " ";
    }
    os << '\n';
}

// n size of string, m compressed string size
// Time complexity: O(n)
// Space complexity: O(max(n, m))
std::string string_compression(std::string_view str) {
    std::string new_str;
    char current_char{str[0]};
    int count{1};
    for(int idx{1}; idx < str.size(); ++idx) {
        auto character = str[idx];
        if(current_char != character) {
            new_str += current_char + std::to_string(count);
            current_char = character;
            count = 1;
        }
        else {
            ++count;
        }
    }
    new_str += current_char + std::to_string(count);
    return new_str.size() < str.size() ? new_str : std::string(str);
}

int main() {
    test_normal(string_compression);
}