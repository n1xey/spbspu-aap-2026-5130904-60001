#include <iostream>

int main()
{
  int current = 0;
  std::cin >> current;
  if (std::cin.fail())
  {
    std::cerr << "Error: input is not a valid number\n";
    return 1;
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
      if (current % previous == 0)
      {
        ++divisible_count;
      }
    }

    if (length >= 2 && before_previous > 0 && previous > 0 && current > 0)
    {
      long long a = before_previous;
      long long b = previous;
      long long c = current;
      if (a * a + b * b == c * c)
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
      return 1;
    }
  }

  std::cout << "pth-trp = " << triples_count << '\n';

  if (length < 2)
  {
    std::cerr << "Sequence too short to compute div-rem\n";
    return 2;
  }

  std::cout << "div-rem = " << divisible_count << '\n';
  return 0;
}
