#include <cstddef>
#include <iostream>
#include <limits>

int main()
{
  constexpr int invalid_input_code = 1;
  constexpr int internal_error_code = 2;
  constexpr int max_int = std::numeric_limits< int >::max();

  int st = 0;
  int nd = 0;
  int rd = 0;

  size_t length = 0;
  size_t triples_count = 0;
  size_t divisible_count = 0;

  while ((std::cin >> rd) && (rd != 0))
  {
    if (length >= 1)
    {
      if ((nd == -1) || ((rd % nd) == 0))
      {
        ++divisible_count;
      }
    }

    if ((st > 0) && (nd > 0) && (rd > 0))
    {
      if ((st > max_int / st) || (nd > max_int / nd) || (rd > max_int / rd))
      {
        std::cerr << "Error: overflow in pth-trp\n";
        return internal_error_code;
      }
      if ((st * st) > (max_int - (nd * nd)))
      {
        std::cerr << "Error: overflow in pth-trp\n";
        return internal_error_code;
      }
      if (((st * st) + (nd * nd)) == (rd * rd))
      {
        ++triples_count;
      }
    }

    st = nd;
    nd = rd;
    ++length;
  }

  if (std::cin.fail())
  {
    std::cerr << "Error: input is not a valid number\n";
    return invalid_input_code;
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
