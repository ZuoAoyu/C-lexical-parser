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

void Scanner::parse() {
  while (true) {
    Token token{nextToken()};

    if (token.line != m_line) {
      std::cout << token.line << ' ';
      m_line = token.line;
    } else {
      std::cout << "   | ";
    }
    std::cout << std::setw(2) << static_cast<int>(token.type) << " '"
              << m_source.substr(token.start, token.length) << "'\n";

    if (token.type == TokenType::EOF_) {
      break;
    }
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

Token Scanner::makeToken(TokenType type) {
  Token token{.type = type,
              .start = m_start,
              .length = (m_current - m_start),
              .line = m_line};

  return token;
}

TokenType Scanner::checkKeyword(int start, const std::string &rest,
                                TokenType type) {
  size_t length_total{m_current - m_start}; // token 总长度
  size_t length_rest{rest.size()};

  if (start + length_rest == length_total &&
      m_source.substr(m_start + start, length_rest) == rest) {
    return type;
  }

  return TokenType::IDENTIFIER;
}

TokenType Scanner::isIdentifierOrKeyword() {
  char c{m_source[m_start]};

  // Trie 树
  switch (c) {
  case 'b':
    return checkKeyword(1, "reak", TokenType::BREAK);
    break;
  case 'c':
    if (m_source[m_start + 1] == 'a') {
      return checkKeyword(2, "se", TokenType::CASE);
    } else if (m_source[m_start + 1] == 'h') {
      return checkKeyword(2, "ar", TokenType::CHAR);
    } else if (m_source[m_start + 1] == 'o' && m_source[m_start + 2] == 'n') {
      if (m_source[m_start + 3] == 't') {
        return checkKeyword(4, "inue", TokenType::CONTINUE);
      } else if (m_source[m_start + 3] == 's') {
        return checkKeyword(4, "t", TokenType::CONST);
      }
    }
    break;
  case 'd':
    if (m_source[m_start + 1] == 'e') {
      return checkKeyword(2, "fault", TokenType::DEFAULT);
    } else if (m_source[m_start + 1] == 'o') {
      return checkKeyword(2, "uble", TokenType::DOUBLE);
    }
    break;
  case 'e':
    if (m_source[m_start + 1] == 'n') {
      return checkKeyword(2, "um", TokenType::ENUM);
    } else if (m_source[m_start + 1] == 'l') {
      return checkKeyword(2, "se", TokenType::ELSE);
    }
    break;
  case 'f':
    if (m_source[m_start + 1] == 'l') {
      return checkKeyword(2, "oat", TokenType::FLOAT);
    } else if (m_source[m_start + 1] == 'o') {
      return checkKeyword(2, "r", TokenType::FOR);
    }
    break;
  case 'g':
    return checkKeyword(1, "oto", TokenType::GOTO);
    break;
  case 'i':
    if (m_source[m_start + 1] == 'f') {
      return checkKeyword(2, "", TokenType::IF);
    } else if (m_source[m_start + 1] == 'n') {
      return checkKeyword(2, "t", TokenType::INT);
    }
    break;
  case 'l':
    return checkKeyword(1, "ong", TokenType::LONG);
    break;
  case 'r':
    return checkKeyword(1, "eturn", TokenType::RETURN);
    break;
  case 's':
    if (m_source[m_start + 1] == 'h') {
      return checkKeyword(2, "ort", TokenType::SHORT);
    } else if (m_source[m_start + 1] == 'i') {
      if (m_source[m_start + 2] == 'g') {
        return checkKeyword(3, "ned", TokenType::SIGNED);
      } else if (m_source[m_start + 2] == 'z') {
        return checkKeyword(3, "eof", TokenType::SIZEOF);
      }
    } else if (m_source[m_start + 1] == 't') {
      return checkKeyword(2, "ruct", TokenType::STRUCT);
    } else if (m_source[m_start + 1] == 'w') {
      return checkKeyword(2, "itch", TokenType::SWITCH);
    }
    break;
  case 't':
    return checkKeyword(1, "ypedef", TokenType::TYPEDEF);
    break;
  case 'u':
    if (m_source[m_start + 1] == 'n') {
      if (m_source[m_start + 2] == 's') {
        return checkKeyword(3, "igned", TokenType::UNSIGNED);
      } else if (m_source[m_start + 2] == 'i') {
        return checkKeyword(3, "on", TokenType::UNION);
      }
    }
    break;
  case 'v':
    return checkKeyword(1, "oid", TokenType::VOID);
    break;
  case 'w':
    return checkKeyword(1, "hile", TokenType::WHILE);
    break;
  }

  // 是标识符
  return TokenType::IDENTIFIER;
}

bool Scanner::ifMatchThenTakeOut(char expected) {
  if (isAtEnd()) {
    return false;
  }
  if (peek() != expected) {
    return false;
  }

  ++m_current;
  return true;
}

Token Scanner::nextToken() {
  // 跳过空白字符和注释
  skipWhitespaces(m_source, m_current, m_line);
  m_start = m_current;

  if (isAtEnd()) {
    return makeToken(TokenType::EOF_);
  }

  char c{takeOutOne()};

  if (isAlpha(c)) {
    // 取出整个 token 的字符
    while (isAlpha(peek()) || std::isdigit(c)) {
      takeOutOne();
    }

    // 该 token 可能是标识符，也可能是关键字，需要进一步识别
    TokenType type{isIdentifierOrKeyword()};
    return makeToken(type);
  }

  if (std::isdigit(c)) {
    processNumber();
  }

  switch (c) {
  // single-character tokens
  case '(':
    return makeToken(TokenType::LEFT_PAREN);
  case '[':
    return makeToken(TokenType::LEFT_BRACKET);
  case '{':
    return makeToken(TokenType::LEFT_BRACE);
  case ')':
    return makeToken(TokenType::RIGHT_PAREN);
  case ']':
    return makeToken(TokenType::RIGHT_BRACKET);
  case '}':
    return makeToken(TokenType::RIGHT_BRACE);
  case ',':
    return makeToken(TokenType::COMMA);
  case '.':
    return makeToken(TokenType::DOT);
  case ';':
    return makeToken(TokenType::SEMICOLON);
  case '~':
    return makeToken(TokenType::TILDE);
  // one or two characters tokens
  case '+':
    if (ifMatchThenTakeOut('+'))
      return makeToken(TokenType::PLUS_PLUS);
    else if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::PLUS_EQUAL);
    else
      return makeToken(TokenType::PLUS);
  case '-':
    if (ifMatchThenTakeOut('-'))
      return makeToken(TokenType::MINUS_MINUS);
    else if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::MINUS_EQUAL);
    else if (ifMatchThenTakeOut('>'))
      return makeToken(TokenType::MINUS_GREATER);
    else
      return makeToken(TokenType::MINUS);
  case '*':
    if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::STAR_EQUAL);
    else
      return makeToken(TokenType::STAR);
  case '/':
    if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::SLASH_EQUAL);
    else
      return makeToken(TokenType::SLASH);
  case '%':
    if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::PERCENT_EQUAL);
    else
      return makeToken(TokenType::PERCENT);
  case '&':
    if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::AMPER_EQUAL);
    else if (ifMatchThenTakeOut('&'))
      return makeToken(TokenType::AMPER_AMPER);
    else
      return makeToken(TokenType::AMPER);
  case '|':
    if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::PIPE_EQUAL);
    else if (ifMatchThenTakeOut('|'))
      return makeToken(TokenType::PIPE_PIPE);
    else
      return makeToken(TokenType::PIPE);
  case '^':
    if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::HAT_EQUAL);
    else
      return makeToken(TokenType::HAT);
  case '=':
    if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::EQUAL_EQUAL);
    else
      return makeToken(TokenType::EQUAL);
  case '!':
    if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::BANG_EQUAL);
    else
      return makeToken(TokenType::BANG);
  case '<':
    if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::LESS_EQUAL);
    else if (ifMatchThenTakeOut('<'))
      return makeToken(TokenType::LESS_LESS);
    else
      return makeToken(TokenType::LESS);
  case '>':
    if (ifMatchThenTakeOut('='))
      return makeToken(TokenType::GREATER_EQUAL);
    else if (ifMatchThenTakeOut('>'))
      return makeToken(TokenType::GREATER_GREATER);
    else
      return makeToken(TokenType::GREATER);

  // various-character tokens
  case '\"':
    return processString();
  case '\'':
    return processCharacter();
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  case '0':
    return processNumber();
  default:
    isIdentifierOrKeyword();
  }

  return makeToken(TokenType::ERROR);
}

Token Scanner::processString() {
  while (peek() != '\"') {
    takeOutOne();

    if (peek() == '\n') {
      // 字符串不能跨行
      return makeToken(TokenType::ERROR);
    }
  }

  takeOutOne();
  return makeToken(TokenType::STRING);
}

Token Scanner::processCharacter() {
  // 以字符 ' 开头且以字符 ' 结尾，且不能跨行
  int sum{0};
  while (peek() != '\'' && sum != 2) {
    takeOutOne();
    ++sum;
    if (peek() != '\'') {
      return makeToken(TokenType::CHARACTER);
    }
  }

  return makeToken(TokenType::ERROR);
}

Token Scanner::processNumber() {
  // 判断数字是否合法，NUMBER 的规则：
  // 可以包含数字和最多一个'.'号；'.'号前面要有数字；'.'号后面也要有数字。
  // 合法的 NUMBER 的例子：123, 3.14
  // 不合法的 NUMBER 的例子：123., .14

  while (std::isdigit(peek())) {
    takeOutOne();
  }

  if (peek() == '.') {
    takeOutOne();
    if (!std::isdigit(peek())) {
      return makeToken(TokenType::ERROR);
    } else {
      while (std::isdigit(peek())) {
        takeOutOne();
      }
    }
  }

  return makeToken(TokenType::NUMBER);
}
