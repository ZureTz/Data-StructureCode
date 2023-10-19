#include <iostream>
using std::cin;
using std::cout;

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int a = 0, b = 1, c = 2;
  (a = b) = c;
  cout << a;

  return 0;
}