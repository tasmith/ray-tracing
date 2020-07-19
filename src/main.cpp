// simple main.cpp
#include <fmt/format.h>
#include <iostream>

int main()
{
  std::string s = fmt::format("{}", 42);
  std::cout << s << '\n';
}
