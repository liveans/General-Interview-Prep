#include <array>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

#define test_normal(test_data) test_normal_func((test_data), #test_data)

constexpr std::size_t matrix_size_bigger = 4;

std::uint32_t test_data_2[matrix_size_bigger][matrix_size_bigger]{
    {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

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

template <std::size_t N>
void matrix_swap(std::uint32_t (&arr)[N][N], layer l1, layer l2) {
  for (; l1.row_start < l1.row_end; l1.row_start++, l2.row_start++) {
    for (auto l1_col_start{l1.col_start}, l2_col_start{l2.col_start};
         l1_col_start < l1.col_end; l1_col_start++, l2_col_start++) {
      std::swap(arr[l1.row_start][l1_col_start],
                arr[l2.row_start][l2_col_start]);
    }
  }
}

template <std::size_t N> void rotate_matrix(std::uint32_t (&arr)[N][N]) {
  auto max_idx{N - 1};
  for (std::size_t row{}; row < N / 2; ++row) {
    for (std::size_t col{}; col < max_idx - 1; ++col) {
      auto item = arr[row][col];
      arr[row][col] = arr[col][max_idx - row];
      arr[col][max_idx - row] = arr[max_idx - row][max_idx - col];
      arr[max_idx - row][max_idx - col] = arr[max_idx - col][row];
      arr[max_idx - col][row] = item;
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
  os << "Before rotation:\n";
  print_matrix(test_data, os);
  rotate_matrix(test_data);
  os << "After rotation:\n";
  print_matrix(test_data, os);
  rotate_matrix(test_data);
  os << "After rotation:\n";
  print_matrix(test_data, os);
  rotate_matrix(test_data);
  os << "After rotation:\n";
  print_matrix(test_data, os);
  rotate_matrix(test_data);
  os << "After rotation:\n";
  print_matrix(test_data, os);
}

int main() { test_normal(test_data_2); }