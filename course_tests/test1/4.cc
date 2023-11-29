#include <iostream>
using std::cout;

struct Person {
  const int number;
  const int password;

  Person *prev, *next;

  Person(int number, int password, Person *prev = nullptr,
         Person *next = nullptr)
      : number(number), password(password), prev(prev ? prev : this),
        next(next ? next : this) {}
};

void outputSeq(Person *head, int password) {
  auto ptr = head->next;
  while (head->next != head) {
    while (--password > 0) {
      ptr = ptr->next;
      if (ptr == head) {
        ptr = ptr->next;
      }
    }

    password = ptr->password;
    cout << ptr->number << ' ';
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;

    auto temp = ptr;
    ptr = ptr->next;
    if (ptr == head) {
      ptr = ptr->next;
    }
    delete temp;
  }
}

int main(int argc, char const *argv[]) {

  int nPersons, password;
  std::cin >> nPersons >> password;

  Person *firstHead = new Person(0, 0);
  {
    auto ptr = firstHead;
    for (int i = 1; i <= nPersons; ++i, ptr = ptr->next) {
      int currentPassword;
      std::cin >> currentPassword;
      auto tmp = new Person(i, currentPassword, ptr, ptr->next);
      ptr->next->prev = tmp;
      ptr->next = tmp;
    }
  }

  outputSeq(firstHead, password);

  return 0;
}