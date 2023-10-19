#include <iostream>
using std::cin;
using std::cout;

struct ListNode {
  int val;
  ListNode *next;

  ListNode(int val = 0, ListNode *next = nullptr) : val(val), next(next) {}
  ~ListNode() {
    if (next == nullptr) {
      return;
    }
    delete next;
  }
};

void print(ListNode *head) {
  ListNode *temp = head->next;
  while (temp != nullptr) {
    cout << temp->val << ' ';
    temp = temp->next;
  }
}

void findAndDelete(ListNode *head, int toBeDel) {
  ListNode *prev = head, *now = head->next;
  while (now != nullptr) {
    if (now->val != toBeDel) {
      prev = prev->next;
      now = now->next;
      continue;
    }

    // else the value is tobedel
    prev->next = now->next;
    ListNode *temp = now;
    now = now->next;
    temp->next = nullptr;
    delete temp;
  }
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n;
  ListNode *const head = new ListNode();
  {
    int temp;
    ListNode *ptr = head;
    for (int i = 0; i < n; i++) {
      cin >> temp;
      ptr->next = new ListNode(temp);
      ptr = ptr->next;
    }
  }

  int toBeDel;
  cin >> toBeDel;
  findAndDelete(head, toBeDel);
  print(head);

  delete head;
  return 0;
}