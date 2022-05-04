#include <iostream>
#include <string>
#include <unordered_set>

std::string unique_sorted{"abcdefg"};
std::string unique{"badcfehg"};
std::string not_unique{"bbaaccdd"};
std::string not_unique_one_char{"bacdeef"};

template <typename Iter>
bool is_unique_hash_table(Iter begin, Iter end) {
    std::unordered_set<typename Iter::value_type> temp{};
    for(; begin != end; ++begin) {
        if(temp.contains(*begin)) {
            return false;
        }
        temp.insert(*begin);
    }
    return true;
}



int main() {
    std::cout << is_unique_hash_table(unique_sorted.begin(), unique_sorted.end())
              << is_unique_hash_table(unique.begin(), unique.end())
              << is_unique_hash_table(not_unique.begin(), not_unique.end())
              << is_unique_hash_table(not_unique_one_char.begin(), not_unique_one_char.end());
}