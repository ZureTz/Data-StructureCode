#include <iostream>
#include <string>
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

Digit *mergeNumAdd(Digit *const head1, Digit *const head2) {
  Digit *result = new Digit(1);

  auto p1 = head1->prev, p2 = head2->prev;
  int tenth = 0, oneth = 0;
  while (p1 != head1 && p2 != head2) {
    oneth = p1->num + p2->num + tenth;
    tenth = oneth / 10;
    oneth %= 10;

    auto tmp = new Digit(oneth, result, result->next);
    result->next->prev = tmp;
    result->next = tmp;

    p1 = p1->prev;
    p2 = p2->prev;
  }

  while (p1 != head1) {
    oneth = p1->num + tenth;
    tenth = oneth / 10;
    oneth %= 10;

    auto tmp = new Digit(oneth, result, result->next);
    result->next->prev = tmp;
    result->next = tmp;
    p1 = p1->prev;
  }

  while (p2 != head2) {
    oneth = p2->num + tenth;
    tenth = oneth / 10;
    oneth %= 10;

    auto tmp = new Digit(oneth, result, result->next);
    result->next->prev = tmp;
    result->next = tmp;

    p2 = p2->prev;
  }

  auto tmp = new Digit(tenth, result, result->next);
  result->next->prev = tmp;
  result->next = tmp;

  while (result->next->num == 0) {
    result->next = result->next->next;
  }
  return result;
}

Digit *mergeNumSub(Digit *const head1, Digit *const head2) {
  Digit *result = new Digit(1);

  auto p1 = head1->prev, p2 = head2->prev;
  int tenth = 0, oneth = 0;
  while (p1 != head1 && p2 != head2) {
    oneth = p1->num - p2->num - tenth;
    if (oneth < 0) {
      tenth = 1;
      oneth = (oneth % 10) + 10;
    } else {
      tenth = 0;
    }

    auto tmp = new Digit(oneth, result, result->next);
    result->next->prev = tmp;
    result->next = tmp;

    p1 = p1->prev;
    p2 = p2->prev;
  }

  while (p1 != head1) {
    oneth = p1->num - tenth;
    if (oneth < 0) {
      tenth = 1;
      oneth = (oneth % 10) + 10;
    } else {
      tenth = 0;
    }
    auto tmp = new Digit(oneth, result, result->next);
    result->next->prev = tmp;
    result->next = tmp;
    p1 = p1->prev;
  }

  while (result->next->num == 0) {
    result->next = result->next->next;
  }
  return result;
}

void output(Digit *const head) {
  std::string temp;
  auto ptr = head->next;
  while (ptr != head) {
    temp += std::to_string(ptr->num);
    ptr = ptr->next;
  }

  int count = 0;
  for (int it = temp.size() - 1; it >= 0; --it, ++count) {
    if ((it > 0) && count == 3) {
      temp.insert(it, 1, ',');
      --it;
      count = 0;
    }
  }

  if (head->num < 0) {
    temp.insert(0, 1, '-');
  }

  cout << temp << '\n';
}

int main(int argc, char const *argv[]) {

  Digit *num1Head = new Digit(1);
  int length1 = 0;
  char isReversed1;
  {
    std::vector<int> tempNums;
    isReversed1 = std::cin.peek();
    if (isReversed1 == '-') {
      std::cin.get();
      num1Head->num = -1;
    }

    char last = 0;
    while (last != '\n') {
      int low;
      (std::cin >> low).get(last);
      tempNums.push_back(low);
      int temp = low;
      while (temp) {
        length1++;
        temp /= 10;
      }
    }
    for (auto it = tempNums.end() - 1; it >= tempNums.begin(); --it) {
      putDigit(num1Head, *it);
    }
  }
  // output(num1Head);
  // cout << length1 << '\n';

  Digit *num2Head = new Digit(1);
  int length2 = 0;
  char isReversed2;

  {
    std::vector<int> tempNums;
    isReversed2 = std::cin.peek();
    if (isReversed2 == '-') {
      std::cin.get();
      num2Head->num = -1;
    }

    char last = 0;
    while (last != '\n') {
      int low;
      (std::cin >> low).get(last);
      tempNums.push_back(low);
      int temp = low;
      while (temp) {
        length2++;
        temp /= 10;
      }
    }
    for (auto it = tempNums.end() - 1; it >= tempNums.begin(); --it) {
      putDigit(num2Head, *it);
    }
  }
  // output(num2Head);
  // cout << length2 << '\n';

  auto abslessthan = [=]() {
    if (length1 == length2) {
      return num1Head->next->num < num2Head->next->num;
    }
    return length1 < length2;
  };

  if (isReversed1 == '-') {
    if (isReversed2 == '-') {
      auto res = mergeNumAdd(num1Head, num2Head);
      res->num = -1;
      output(res);
      return 0;
    }
    if (abslessthan()) {
      output(mergeNumSub(num2Head, num1Head));
      return 0;
    }

    auto res = mergeNumSub(num1Head, num2Head);
    res->num = -1;
    output(res);

    return 0;
  }

  // 1 is not reversed
  if (isReversed2 != '-') {
    output(mergeNumAdd(num1Head, num2Head));
    return 0;
  }

  if (abslessthan()) {
    auto res = mergeNumSub(num2Head, num1Head);
    res->num = -1;
    output(res);
    return 0;
  }

  output(mergeNumSub(num1Head, num2Head));

  return 0;
}
