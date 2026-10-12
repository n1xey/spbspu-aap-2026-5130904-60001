#include <iostream>

int main()
{
  const int invalid_input_code = 1;
  const int internal_error_code = 2;

  int current = 0;
  std::cin >> current;
  if (std::cin.fail())
  {
    std::cerr << "Error: input is not a valid number\n";
    return invalid_input_code;
  }
  int previous = 0;
  int before_previous = 0;
  int length = 0;
  int triples_count = 0;
  int divisible_count = 0;
  while (current != 0)
  {
    if (length >= 1)
    {
      if ((current % previous) == 0)
      {
        ++divisible_count;
      }
    }

    if ((length >= 2) && (before_previous > 0) && (previous > 0) && (current > 0))
    {
      const long long a = before_previous;
      const long long b = previous;
      const long long c = current;
      if (((a * a) + (b * b)) == (c * c))
      {
        ++triples_count;
      }
    }
    before_previous = previous;
    previous = current;
    ++length;
    std::cin >> current;
    if (std::cin.fail())
    {
      std::cerr << "Error: input is not a valid number\n";
      return invalid_input_code;
    }
  }

  std::cout << "pth-trp = " << triples_count << '\n';

  if (length < 2)
  {
    std::cerr << "Sequence too short to compute div-rem\n";
    return internal_error_code;
  }
  std::cout << "div-rem = " << divisible_count << '\n';
  return 0;
}
