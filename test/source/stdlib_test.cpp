#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "stdlib" ? 0 : 1;
}
