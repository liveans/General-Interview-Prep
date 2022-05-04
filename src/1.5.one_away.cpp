#include <iostream>
#include <ostream>
#include <vector>
#include <unordered_map>

#define test_normal(x) test_func(x, #x)

std::vector<std::pair<std::string, std::string>> test_data{
    {"pale", "ple"},
    {"pales", "pale"},
    {"pale", "bale"},
    {"pale", "bake"}
};

template <typename Func>
void test_func(Func func, std::string_view func_name,std::ostream& os = std::cout) {
    os << func_name << ": ";
    for(auto item : test_data) {
        os << func(item);
    }
    os << '\n';
}

// Assume n is the bigger string size
// Time complexity: O(n)
// Space complexity: O(n)
bool one_away_check(const std::pair<std::string, std::string>& pair) {
    const auto& [str1, str2] = pair;
    auto diff{std::max(str1.size(), str2.size()) - std::min(str1.size(), str2.size())};
    if(diff > 1) return false;
    bool different_size{diff != 0};

    std::unordered_map<char, int> values{};

    for(auto c : str1) {
        values[c]++;
    }

    for(auto c : str2) {
        values[c]--;
    }

    int sum{};
    for(const auto&[character, count] : values) {
        sum += std::abs(count);
    }

    return different_size ? (sum == 1) : (sum == 2);
}

int main() {
    test_normal(one_away_check);
}