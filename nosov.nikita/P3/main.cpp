#include <cstddef>
#include <fstream>
#include <iostream>
#include <new>

namespace nosov {
  bool readMatrix(std::istream& in, int* matrix, std::size_t rows, std::size_t cols)
  {
    for (std::size_t i = 0; i < rows * cols; ++i) {
      in >> matrix[i];
      if (!in) {
        return false;
      }
    }
    return true;
  }

  void writeMatrix(std::ostream& out, const int* matrix, std::size_t rows, std::size_t cols)
  {
    out << rows << " " << cols;
    for (std::size_t i = 0; i < rows * cols; ++i) {
      out << " " << matrix[i];
    }
  }

  std::size_t findSeriesColumn(const int* matrix, std::size_t rows, std::size_t cols)
  {
    if (rows == 0 || cols == 0) {
      return 0;
    }
    std::size_t best_column = 0;
    std::size_t best_length = 1;
    for (std::size_t j = 0; j < cols; ++j) {
      std::size_t length = 1;
      for (std::size_t i = 1; i < rows; ++i) {
        if (matrix[i * cols + j] == matrix[(i - 1) * cols + j]) {
          ++length;
        } else {
          length = 1;
        }
        if (length > best_length) {
          best_length = length;
          best_column = j;
        }
      }
    }
    return best_column + 1;
  }

  int processMatrix(std::istream& in, const char* output_name, int* matrix, std::size_t rows, std::size_t cols)
  {
    if (!readMatrix(in, matrix, rows, cols)) {
      std::cerr << "Can not read matrix\n";
      return 2;
    }
    const std::size_t column = findSeriesColumn(matrix, rows, cols);

    std::ofstream out(output_name);
    if (!out) {
      std::cerr << "Can not open output file\n";
      return 2;
    }
    writeMatrix(out, matrix, rows, cols);
    out << "\n";
    out << column << "\n";
    return 0;
  }
}

int main(int argc, char** argv)
{
  const int argumentsCount = 4;
  if (argc < argumentsCount) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > argumentsCount) {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  const char* const num = argv[1];
  const bool isFixed = (num[0] == '1' && num[1] == '\0');
  const bool isDynamic = (num[0] == '2' && num[1] == '\0');
  if (!isFixed && !isDynamic) {
    std::cerr << "First parameter is wrong\n";
    return 1;
  }

  std::ifstream in(argv[2]);
  if (!in) {
    std::cerr << "Can not open input file\n";
    return 2;
  }
  std::size_t rows = 0;
  std::size_t cols = 0;
  in >> rows >> cols;
  if (!in) {
    std::cerr << "Can not read matrix size\n";
    return 2;
  }

  if (isFixed) {
    const std::size_t maxSize = 10000;
    if (rows * cols > maxSize) {
      std::cerr << "Matrix is too big\n";
      return 2;
    }
    int matrix[maxSize] = {};
    return nosov::processMatrix(in, argv[3], matrix, rows, cols);
  }

  int* matrix = nullptr;
  try {
    matrix = new int[rows * cols];
  } catch (const std::bad_alloc&) {
    std::cerr << "Not enough memory\n";
    return 2;
  }
  const int result = nosov::processMatrix(in, argv[3], matrix, rows, cols);
  delete[] matrix;
  return result;
}
