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

