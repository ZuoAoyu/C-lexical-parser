#ifndef _TOKEN_TYPE
#define _TOKEN_TYPE

#include <unordered_map>
#include <string>

enum class TokenType {
    // single-character tokens
    LEFT_PAREN, RIGHT_PAREN,		// '(', ')'
    LEFT_BRACKET, RIGHT_BRACKET,	// '[', ']'
    LEFT_BRACE, RIGHT_BRACE,  		// '{', '}'
    COMMA, DOT, SEMICOLON,	// ',', '.', ';'
    TILDE,  // '~'
    // one or two character tokens
    PLUS, PLUS_PLUS, PLUS_EQUAL, // '+', '++', '+='
    // '-', '--', '-=', '->'
    MINUS, MINUS_MINUS, MINUS_EQUAL, MINUS_GREATER,
    STAR, STAR_EQUAL,			// '*', '*='
    SLASH, SLASH_EQUAL, 		// '/', '/=', 
    PERCENT, PERCENT_EQUAL, 	// '%', '%='
    AMPER, AMPER_EQUAL, AMPER_AMPER, 	// '&', '&=', '&&'
    PIPE, PIPE_EQUAL, PIPE_PIPE,		// '|', '|=', '||'
    HAT, HAT_EQUAL, 		// '^', '^='
    EQUAL, EQUAL_EQUAL, 	// '=', '=='
    BANG, BANG_EQUAL,	  	// '!', '!='
    LESS, LESS_EQUAL, LESS_LESS, 				// '<', '<=', '<<'
    GREATER, GREATER_EQUAL, GREATER_GREATER, 	// '>', '>=', '>>' 
    // 字面值: 标识符, 字符, 字符串, 数字
    IDENTIFIER, CHARACTER, STRING, NUMBER,
    // 关键字
    SIGNED, UNSIGNED,
    CHAR, SHORT, INT, LONG,
    FLOAT, DOUBLE,
    STRUCT, UNION, ENUM, VOID,
    IF, ELSE, SWITCH, CASE, DEFAULT,
    WHILE, DO, FOR,
    BREAK, CONTINUE, RETURN, GOTO,
    CONST, SIZEOF, TYPEDEF,
    // 辅助Token
    ERROR, EOF_
};

/* X macro 实现 根据枚举值打印枚举成员的名称 */

#define LIST_OF_ENUM \
    X(LEFT_PAREN) \
    X(RIGHT_PAREN) \
    X(LEFT_BRACKET) \
    X(RIGHT_BRACKET) \
    X(LEFT_BRACE) \
    X(RIGHT_BRACE) \
    X(COMMA) \
    X(DOT) \
    X(SEMICOLON) \
    X(TILDE) \
    X(PLUS) \
    X(PLUS_PLUS) \
    X(PLUS_EQUAL) \
    X(MINUS) \
    X(MINUS_MINUS) \
    X(MINUS_EQUAL) \
    X(MINUS_GREATER) \
    X(STAR) \
    X(STAR_EQUAL) \
    X(SLASH) \
    X(SLASH_EQUAL) \
    X(PERCENT) \
    X(PERCENT_EQUAL) \
    X(AMPER) \
    X(AMPER_EQUAL) \
    X(AMPER_AMPER) \
    X(PIPE) \
    X(PIPE_EQUAL) \
    X(PIPE_PIPE) \
    X(HAT) \
    X(HAT_EQUAL) \
    X(EQUAL) \
    X(EQUAL_EQUAL) \
    X(BANG) \
    X(BANG_EQUAL) \
    X(LESS) \
    X(LESS_EQUAL) \
    X(LESS_LESS) \
    X(GREATER) \
    X(GREATER_EQUAL) \
    X(GREATER_GREATER) \
    X(IDENTIFIER) \
    X(CHARACTER) \
    X(STRING) \
    X(NUMBER) \
    X(SIGNED) \
    X(UNSIGNED) \
    X(CHAR) \
    X(SHORT) \
    X(INT) \
    X(LONG) \
    X(FLOAT) \
    X(DOUBLE) \
    X(STRUCT) \
    X(UNION) \
    X(ENUM) \
    X(VOID) \
    X(IF) \
    X(ELSE) \
    X(SWITCH) \
    X(CASE) \
    X(DEFAULT) \
    X(WHILE) \
    X(DO) \
    X(FOR) \
    X(BREAK) \
    X(CONTINUE) \
    X(RETURN) \
    X(GOTO) \
    X(CONST) \
    X(SIZEOF) \
    X(TYPEDEF) \
    X(ERROR) \
    X(EOF_) 


#define X(name) {TokenType::name, #name},

inline std::unordered_map<TokenType, std::string> STR {
    LIST_OF_ENUM
};

#undef X
#endif
