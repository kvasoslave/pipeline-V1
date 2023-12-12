#include <iostream>
#include <string>

#include "pipeline.h"

int mul_by_2(int x) { return x * 2; } // ������ ������� �������

int main() {
  using namespace pipeline;
  std::string str = "Hello World!";
  auto pipeline = str | std::size<std::string> | [](auto x) { return x * 2; } |
                  [](auto x) { std::cout << x; };
  pipeline(); // ������� 24

  auto pipeline2 = 7 | to_callable(mul_by_2);

  std::cout << std::endl
            << mul_by_2(pipeline2()) << std::endl; // ��� ������, ������� 28
}
