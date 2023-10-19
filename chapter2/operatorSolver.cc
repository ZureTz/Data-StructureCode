#include "solver"
#include <cstring>
#include <iostream>

int main(int argc, char const *argv[]) {
  if (argc <= 1) {
    std::cerr << "Expression not provided." << std::endl;
    exit(EXIT_FAILURE);
  }
  if (strstr(argv[1], ".")) {
    std::cout << Solver::decoder<double>(argv[1]);
    return 0;
  }
  std::cout << Solver::decoder<long long>(argv[1]);
  return 0;
}