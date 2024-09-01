#include "scanner.h"
#include "test.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: scanner [path]\n");
    exit(1);
  }

  fs::path src_file{argv[1]};
  Scanner scanner{src_file};

  {
    // 测试 文件读取
    Test::testReadFile();
  }

  {
    // 测试 跳过空白符
    Test::testSkipWhiteSpaces();
  }

  scanner.parse();

  return 0;
}
