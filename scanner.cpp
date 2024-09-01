#include "scanner.h"
#include <fstream>
#include <iostream>

Scanner::Scanner(std::string source) : m_source{std::move(source)} {}
Scanner::Scanner(std::filesystem::path filepath)
    : m_filepath{std::move(filepath)}, m_source{readFile(filepath)} {}

std::string Scanner::readFile(std::filesystem::path filepath) {
  std::ifstream file{filepath};

  if (!file.good()) {
    std::cerr << "Error while opening output file!\n";
    throw std::runtime_error{"Failed to open file: " + filepath.string()};
  }

  std::ostringstream ss;
  ss << file.rdbuf(); // 将文件内容读入字符串流

  return ss.str();
}

void Scanner::parse() const {
  size_t start{0};
  size_t current{0};
  size_t line{0};

  while (true) {
  }
}

void Scanner::skipWhitespaces(const std::string &source, size_t &current,
                              size_t &line) {
  std::string_view source_view{source};
  std::string_view parsing_view{source_view.substr(current)};

  for (auto iter{parsing_view.begin()}, end{parsing_view.end()}; iter != end;
       ++iter) {
    switch (*iter) {
    case ' ':
    case '\r':
    case '\t':
      ++current;
      break;
    case '\n':
      ++line;
      ++current;
      break;
    case '/': // 跳过注释
      if (*(iter + 1) != '/') {
        return;
      }
      while (iter != end && *(++iter) != '\n') {
        ++current;
      }
      break;
    default:
      return;
    }
  }
}
