#include <iostream>
#include <vector>
using std::cout;

struct Digit {
  int num;
  Digit *prev, *next;
  Digit(int num, Digit *prev = nullptr, Digit *next = nullptr)
      : num(num % 10), prev((prev ? prev : this)), next((next ? next : this)){};
};

void putDigit(Digit *const dest, int low, int high = 0) {
  Digit *ptr = dest;
  while (low) {
    int lastDigit = low % 10;
    low /= 10;
    auto tmp = new Digit(lastDigit, ptr, ptr->next);
    ptr->next->prev = tmp;
    ptr->next = tmp;
  }

  while (high) {
    int lastDigit = high % 10;
    high /= 10;
    auto tmp = new Digit(lastDigit, ptr, ptr->next);
    ptr->next->prev = tmp;
    ptr->next = tmp;
  }
}

Digit *mergeNum(Digit *const head1, Digit *const head2) {
  Digit *result = new Digit(1);

  auto p1 = head1->prev, p2 = head2->prev;
  int tenth = 0, oneth = 0;
  while (p1 != head1 && p2 != head2) {
    oneth = head1->num * p1->num + head2->num * p2->num + tenth;
    tenth = oneth / 10;
    oneth %= 10;

    if (oneth < 0) {
      result->num = -1;
      oneth = -oneth;
    }
    auto tmp = new Digit(oneth, result, result->next);
    result->next->prev = tmp;
    result->next = tmp;

    p1 = p1->prev;
    p2 = p2->prev;
  }

  if (tenth < 0) {
    result->num = -1;
    tenth = -tenth;
  }
  auto tmp = new Digit(tenth, result, result->next);
  result->next->prev = tmp;
  result->next = tmp;

  return result;
}

void output(Digit *const head) {
  if (head->num < 0) {
    cout << '-';
  }
  auto ptr = head->next;
  while (ptr != head) {
    cout << ptr->num;
    ptr = ptr->next;
  }
}

int main(int argc, char const *argv[]) {

  Digit *num1Head = new Digit(1);
  {
    int negflag = 1;
    std::vector<int> tempNums;
    while (std::cin.peek() != '\n') {
      int low;
      std::cin >> low;
      if (low < 0) {
        negflag = -1;
        low = -low;
      }
      tempNums.push_back(low);
    }
    for (auto it = tempNums.end() - 1; it >= tempNums.begin(); --it) {
      putDigit(num1Head, *it);
    }
    num1Head->num = negflag;
    std::cin.ignore();
  }
  // cout << high4 << ' ' << low4 << '\n';
  // output(num1Head);
  // cout.put('\n');

  Digit *num2Head = new Digit(1);
  {
    int negflag = 1;
    std::vector<int> tempNums;
    while (std::cin.peek() != '\n') {
      int low;
      std::cin >> low;
      if (low < 0) {
        negflag = -1;
        low = -low;
      }
      tempNums.push_back(low);
    }
    for (auto it = tempNums.end() - 1; it >= tempNums.begin(); --it) {
      putDigit(num2Head, *it);
    }
    num2Head->num = negflag;
    std::cin.ignore();
  }
  // cout << high4 << ' ' << low4 << '\n';
  // output(num2Head);
  // cout.put('\n');

  auto res = mergeNum(num1Head, num2Head);
  output(res);
  cout.put('\n');

  return 0;
}