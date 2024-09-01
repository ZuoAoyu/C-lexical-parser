#include "test.h"
#include "scanner.h"
#include <iostream>

void Test::testSkipWhiteSpaces() {
  std::string src = " \t\n\r//hello";
  size_t current{0};
  size_t line{0};
  Scanner::skipWhitespaces(src, current, line);

  std::cout << "answer:\n11 1\nreal:\n";
  std::cout << current << " " << line << '\n';
}

void Test::testReadFile() {
  std::filesystem::path src_file{"test_read_file.md"};
  Scanner scanner{src_file};
  std::cout << "number of characters: " << scanner.getSource().size() << '\n';
}
