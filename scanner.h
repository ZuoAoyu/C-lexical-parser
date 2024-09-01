#ifndef _SCANNER_H
#define _SCANNER_H
#include "token_type.h"
#include <filesystem>
#include <string>

class Test;

struct Token {
  TokenType type; // token 类型
  size_t start;   // token 的起始索引
  size_t length;  // token 的长度
  size_t line;    // 该 token 位于第几行
};

class Scanner {
public:
  friend class Test;
  Scanner(std::string source);
  Scanner(std::filesystem::path filepath);

  const std::string &getSource() const { return m_source; }
  void parse() const;

private:
  static std::string readFile(std::filesystem::path filepath);
  static void skipWhitespaces(const std::string &source, size_t &current,
                              size_t &line);

private:
  std::string m_source{};
  std::filesystem::path m_filepath{};
};

#endif
