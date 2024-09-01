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

  // {
  //   // 测试文件读取是否正常
  //   std::cout << scanner.getSource();
  // }

  {
    // 测试 跳过空白符
    Test::testSkipWhiteSpaces();
  }

  return 0;
}
