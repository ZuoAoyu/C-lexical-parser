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
  void parse();

private:
  static std::string readFile(std::filesystem::path filepath);
  static void skipWhitespaces(const std::string &source, size_t &current,
                              size_t &line);

  bool isAtEnd() { return m_source.begin() + m_current == m_source.end(); }
  static bool isAlpha(char ch) { return std::isalpha(ch) || ch == '_'; }

  Token nextToken();
  Token makeToken(TokenType type);

  Token processString();
  Token processCharacter();
  Token processNumber();

  char takeOutOne() { return m_source[m_current++]; } // 取出字符
  char peek() { return m_source[m_current]; } // 看字符是什么，并不取出
  bool ifMatchThenTakeOut(char expected);

  TokenType isIdentifierOrKeyword();
  TokenType checkKeyword(int start, const std::string &rest, TokenType type);

private:
  std::string m_source{};
  std::filesystem::path m_filepath{};

  size_t m_start{0};   // 当前 token 的起始字符的下标
  size_t m_current{0}; // 当前字符的下标
  size_t m_line{0};    // 当前字符所在行
};

#endif
