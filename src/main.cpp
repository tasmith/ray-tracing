// simple main.cpp
#include <fmt/format.h>
#include <fstream>
#include <iostream>

constexpr int answer {42};

int main()
{
  try {
    std::string s = fmt::format("{}", answer);
    std::cout << s << '\n';
  } catch (...) {
    std::cerr << "Exception in main!" << std::endl;
  }
}
