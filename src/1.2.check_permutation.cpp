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
    {"cacbd", "abccd"},
    {"aabbcc", "abcabc"},
    {"aabbcc", "abcab"}
};

template <typename Func>
void test_func(Func func, std::string_view func_name,std::ostream& os = std::cout) {
    os << func_name << ": ";
    for(auto item : test_data) {
        os << func(item.first, item.second);
    }
    os << '\n';
}

void permutation_helper(std::string s, std::string answer, std::unordered_set<std::string>& permutations) {
    if(s.empty()) permutations.emplace(answer);

    for(std::string_view::size_type i{}; i < s.size(); ++i) {
        auto rest{s.substr(0, i) + s.substr(i + 1)};
        permutation_helper(rest, answer + s[i], permutations);
    }
}

std::unordered_set<std::string> get_permutations(std::string s) {
    std::unordered_set<std::string> permutations;
    permutation_helper(s, "", permutations);
    return permutations;
}

// Time complexity O(n! * n)
// Space complexity O(n!)
bool check_permutation_brute_force(std::string original, std::string check_str) {
    auto permutations{get_permutations(original)};
    return permutations.find(check_str) != permutations.end();
}

// Time complexity O(n)
// Space complexity O(n)
bool check_permutation_with_character_check(std::string original, std::string check_str) {
    if(original.size() != check_str.size()) return false;

    std::unordered_map<char, int> values_original{};
    std::unordered_map<char, int> values_check_str{};
    for(auto character : original) values_original[character]++;
    for(auto character : check_str) values_check_str[character]++;

    for(const auto& item : values_original) {
        if(values_check_str[item.first] != item.second) return false;
    }
    return true;
}

// Time complexity O(n)
// Space complexity O(n)
bool check_permutation_with_character_check_v2(std::string original, std::string check_str) {
    if(original.size() != check_str.size()) return false;

    std::unordered_map<char, int> values{};
    for(auto character : original) values[character]++;
    for(auto character : check_str) values[character]--;

    for(const auto& item : values) {
        if(item.second) return false;
    }
    return true;
}

int main() {
    test_normal(check_permutation_brute_force);
    test_normal(check_permutation_with_character_check);
    test_normal(check_permutation_with_character_check_v2);
}