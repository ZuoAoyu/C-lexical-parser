# 编译 和 使用

```
$ g++ main.cpp scanner.cpp test.cpp -o scanner -std=c++20
$ ./scanner test_result.c
```

分析结果：

```
0    ERROR '#'
   | IDENTIFIER 'include'
   | LESS '<'
   | IDENTIFIER 'stdio'
   | DOT '.'
   | IDENTIFIER 'h'
   | GREATER '>'
2    INT 'int'
   | IDENTIFIER 'main'
   | LEFT_PAREN '('
   | RIGHT_PAREN ')'
   | LEFT_BRACE '{'
3    IDENTIFIER 'printf'
   | LEFT_PAREN '('
   | STRING '"hello world\n"'
   | RIGHT_PAREN ')'
   | SEMICOLON ';'
5    RETURN 'return'
   | NUMBER '0'
   | SEMICOLON ';'
6    RIGHT_BRACE '}'
7    EOF_ ''

```
