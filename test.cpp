#include "test.h"
#include <iostream>

void Test::testSkipWhiteSpaces() {
  std::string src = " \t\n\r//hello";
  size_t current{0};
  size_t line{0};
  Scanner::skipWhitespaces(src, current, line);

  std::cout << current << " " << line << '\n';
}
