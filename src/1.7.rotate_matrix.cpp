#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <vector>
#include <iomanip>

#define test_normal(test_data) test_normal_func((test_data), #test_data)

constexpr std::size_t matrix_size = 2;
constexpr std::size_t matrix_size_bigger = 4;

std::uint32_t test_data_1[matrix_size][matrix_size]{{1, 2}, {3, 4}};
std::uint32_t test_data_2[matrix_size_bigger][matrix_size_bigger]{
    {1, 2, 3, 4}, 
    {5, 6, 7, 8}, 
    {9, 10, 11, 12}, 
    {13, 14, 15, 16}
};

/*
    After first rotation it must be
    2, 4
    1, 3

    After second rotation it must be

    4, 3
    2, 1
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
    for (auto l1_col_start{l1.col_start}, l2_col_start{l2.col_start}; l1_col_start < l1.col_end; l1_col_start++, l2_col_start++) {
      std::swap(arr[l1.row_start][l1_col_start],
                arr[l2.row_start][l2_col_start]);
    }
  }
}

template <std::size_t N> void rotate_matrix(std::uint32_t (&arr)[N][N]) {
  std::array<layer, 4> layer_row_col_indexes{
      layer{0, 0, N / 2, N / 2},
      layer{N / 2, 0, N, N / 2},
      layer{N / 2, N / 2, N, N},
      layer{0, N / 2, N / 2, N},
  };
  matrix_swap(arr, layer_row_col_indexes[0], layer_row_col_indexes[3]);
  matrix_swap(arr, layer_row_col_indexes[1], layer_row_col_indexes[2]);
  matrix_swap(arr, layer_row_col_indexes[1], layer_row_col_indexes[3]);
}

template <std::size_t N> void print_matrix(const std::uint32_t (&arr)[N][N], std::ostream& os = std::cout) {
  for (auto i{0}; i < N; ++i) {
    for (auto k{0}; k < N; ++k) {
      os << arr[i][k] << " ";
    }
    os.put('\n');
  }
}

template <std::size_t N>
void test_normal_func(std::uint32_t(&test_data)[N][N], std::string_view test_data_name, std::ostream& os = std::cout) {
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

int main() {
    test_normal(test_data_1);
    test_normal(test_data_2);
}