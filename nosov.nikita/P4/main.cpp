#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <istream>
#include <new>

namespace nosov {
  char* readLine(std::istream& in)
  {
    const std::size_t growth_factor = 2;
    const std::size_t start_capacity = 16;
    std::size_t capacity = start_capacity;
    char* line = new (std::nothrow) char[capacity];
    if (line == nullptr) {
      return nullptr;
    }
    std::size_t size = 0;
    char symbol = '\0';
    while (in.get(symbol) && (symbol != '\n')) {
      if (size + 1 == capacity) {
        const std::size_t new_capacity = capacity * growth_factor;
        char* const new_line = new (std::nothrow) char[new_capacity];
        if (new_line == nullptr) {
          delete[] line;
          return nullptr;
        }
        std::memcpy(new_line, line, size);
        delete[] line;
        line = new_line;
        capacity = new_capacity;
      }
      line[size] = symbol;
      ++size;
    }
    line[size] = '\0';
    return line;
  }

  std::size_t countDifferentLetters(const char* str)
  {
    const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    std::size_t count = 0;
    for (std::size_t i = 0; alphabet[i] != '\0'; ++i) {
      const int lower = alphabet[i];
      const int upper = std::toupper(lower);
      if ((std::strchr(str, lower) != nullptr) || (std::strchr(str, upper) != nullptr)) {
        ++count;
      }
    }
    return count;
  }

  char* removeVowels(const char* source, char* result)
  {
    const char vowels[] = "aeiou";
    std::size_t result_size = 0;
    for (std::size_t i = 0; source[i] != '\0'; ++i) {
      const int lower = std::tolower(static_cast< unsigned char >(source[i]));
      if (std::strchr(vowels, lower) == nullptr) {
        result[result_size] = source[i];
        ++result_size;
      }
    }
    result[result_size] = '\0';
    return result;
  }
}

int main()
{
  const char* const line = nosov::readLine(std::cin);
  if (line == nullptr) {
    std::cerr << "Not enough memory\n";
    return 1;
  }
  if ((line[0] == '\0') && !std::cin) {
    delete[] line;
    std::cerr << "Empty input\n";
    return 1;
  }
  char* const without_vowels = new (std::nothrow) char[std::strlen(line) + 1];
  if (without_vowels == nullptr) {
    delete[] line;
    std::cerr << "Not enough memory\n";
    return 1;
  }
  std::cout << nosov::countDifferentLetters(line) << "\n";
  std::cout << nosov::removeVowels(line, without_vowels) << "\n";
  delete[] without_vowels;
  delete[] line;
  return 0;
}
