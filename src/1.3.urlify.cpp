#include <iostream>
#include <ostream>
#include <vector>

#define test_normal(x) test_func((x), #x)
#define EXPECT_EQ(x, y) std::cout << std::boolalpha << ((x) == (y)) << std::noboolalpha << '\n'

// Mr_John_Smith____
// Mr_John_Smit____h
// Mr_John_Smi____th
// Mr_John_Sm____ith
// Mr_John_S____mith
// Mr_John_____Smith
// Mr_John__%20Smith

std::vector<std::pair<std::string, int>> test_data{{"Mr John Smith    ", 13}};

template <typename Func>
void test_func(Func func, std::string_view func_name,
               std::ostream &os = std::cout) {
  os << func_name << ": ";
  for (auto item : test_data) {
    os << func(item);
  }
  os << '\n';
}

std::string urlify_str(std::pair<std::string, int> pair) {
  auto &str = pair.first;
  int last_idx = str.size() - 1;
  for (int i = pair.second - 1; i >= 0; --i) {
    if (str[i] != ' ') {
      std::swap(str[i], str[last_idx--]);
    } else {
      str[last_idx - 2] = '%';
      str[last_idx - 1] = '2';
      str[last_idx - 0] = '0';
      last_idx -= 3;
    }
  }
  return str;
}

int main() { 
    test_normal(urlify_str);
    EXPECT_EQ(urlify_str(test_data[0]), "Mr%20John%20Smith");
}