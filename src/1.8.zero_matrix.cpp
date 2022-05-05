#include <array>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <unordered_set>
#include <vector>

#define test_normal(test_data) test_normal_func((test_data), #test_data)

constexpr std::size_t matrix_size_bigger = 4;

std::uint32_t test_data_2[matrix_size_bigger][matrix_size_bigger]{
    {1, 2, 3, 4}, {0, 6, 7, 8}, {9, 10, 0, 12}, {13, 14, 15, 16}};

/*
    After first rotation it must be
    4 8 12 16
    3 7 11 15
    2 6 10 14
    1 5 9  13

    After second rotation it must be
    16 15 14 13
    12 11 10 9
    8  7  6  5
    4  3  2  1
*/

struct layer {
  std::size_t row_start;
  std::size_t col_start;
  std::size_t row_end;
  std::size_t col_end;
};

template <std::size_t N> void zero_matrix_impl(std::uint32_t (&arr)[N][N]) {
  std::unordered_set<int> col_indexes{};
  for (std::size_t row{}; row < N; ++row) {
    for (std::size_t col{}; col < N; ++col) {
      if (col_indexes.contains(col)) {
        continue;
      }
      auto item = arr[row][col];
      if(item == 0) {
          for(int idx{}; idx < N; ++idx) {
              arr[row][idx] = 0;
              arr[idx][col] = 0;
          }
          col_indexes.insert(col);
          break;
      }
    }
  }
}

template <std::size_t N>
void print_matrix(const std::uint32_t (&arr)[N][N],
                  std::ostream &os = std::cout) {
  for (auto i{0}; i < N; ++i) {
    for (auto k{0}; k < N; ++k) {
      os << arr[i][k] << " ";
    }
    os.put('\n');
  }
}

template <std::size_t N>
void test_normal_func(std::uint32_t (&test_data)[N][N],
                      std::string_view test_data_name,
                      std::ostream &os = std::cout) {
  os << test_data_name << ": \n";
  os << "Before zero matrix impl:\n";
  print_matrix(test_data, os);
  zero_matrix_impl(test_data);
  os << "After zero matrix impl:\n";
  print_matrix(test_data, os);
}

int main() { test_normal(test_data_2); }