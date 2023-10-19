#include <cstdlib>
#include <iostream>
#include <type_traits>
using std::cin;
using std::cout;

struct LinkedList {
  int element;
  LinkedList *next;
  LinkedList(int element = 0, LinkedList *next = nullptr)
      : element(element), next(next) {}
  void output() const {
    auto tmp = this->next;
    while (tmp != nullptr) {
      cout << tmp->element << ' ';
      tmp = tmp->next;
    }
    cout << std::endl;
  }

  ~LinkedList() { delete next; }
};

// void sort(LinkedList *const head, int length) {
//   // for (int i = 0; i < length - 1; ++i) {
//   //   for (int j = 0; j < length - 1 - i; ++j) {
//   //     if (arr[j] > arr[j + 1]) {
//   //       swap ///
//   //     }
//   //   }
//   // }
//   for (int i = 0; i < length - 1; ++i) {
//     auto ptr = head->next;
//     for (int j = 0; j < length - 1 - i; j++) {
//       if (ptr->element > ptr->next->element) {
//         std::swap(ptr->element, ptr->next->element);
//       }
//       ptr = ptr->next;
//     }
//   }
// }

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  LinkedList *const head1 = new LinkedList();
  int nList1;
  cin >> nList1;
  {
    auto ptr = head1;
    int temp;
    for (int i = 0; ptr && i < nList1; i++) {
      cin >> temp;
      ptr->next = new LinkedList(temp);
      ptr = ptr->next;
    }
  }

  LinkedList *const head2 = new LinkedList();
  int nList2;
  cin >> nList2;
  {
    auto ptr = head2;
    int temp;
    for (int i = 0; i < nList2; i++) {
      cin >> temp;
      ptr->next = new LinkedList(temp);
      ptr = ptr->next;
    }
  }

  int count = 0;
  LinkedList *const templist = new LinkedList();
  auto ptr1 = head1->next;
  auto ptr3 = templist;
  while (ptr1 != nullptr) {
    auto ptr2 = head2->next;
    while (ptr2 != nullptr) {
      if (ptr2->element == ptr1->element) {
        count++;
        ptr3->next = new LinkedList(ptr1->element);
        ptr3 = ptr3->next;
        break;
      }
      ptr2 = ptr2->next;
    }
    ptr1 = ptr1->next;
  }

  if (count == 0) {
    cout << count << "\n没有公共元素";
    return 0;
  }

  cout << count << std::endl;
  ptr3 = templist->next;
  while (ptr3 != nullptr) {
    cout << ptr3->element << ' ';
    ptr3 = ptr3->next;
  }

  delete head1;
  delete head2;
  delete templist;
  return 0;
}