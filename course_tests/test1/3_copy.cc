// 50
#include <cstring>
#include <iostream>

using namespace std;

struct node {
  node *next;
  char word;
};

node *push(node *head, char word) {
  if (head == NULL || head->word > word) { // 如果要插在头
    node *t = new node;
    t->next = head;
    head = t;
    t->word = word;
  } else {
    node *l = head;
    int flag = 1;
    while (l != NULL) { // 标记重复元素
      if (l->word == word) {
        flag = 0;
        break;
      }
      l = l->next;
    }
    l = head;
    if (flag) { // 如果没有重复元素
      while (l->next != NULL && l->next->word < word) { // 保持升序
        l = l->next;
      }
      node *t = new node; // 插入l之后，l->next之前
      t->word = word;
      t->next = l->next;
      l->next = t;
    }
  }
  return head;
}

node *read_set() {
  node *a = NULL;
  char s[23333] = {0};
  int len;
  // if (scanf("%s", s) != 1) {
  //     exit(0);
  // }
  scanf("%s", s);
  len = strlen(s);
  for (int i = 0; i < len; ++i) {
    a = push(a, s[i]);
  }
  return a;
}

void print_set(node *head) {
  node *l = head;
  while (l != NULL) {
    putchar(l->word);
    l = l->next;
  }
  putchar('\n');
}

node *sum(node *head1, node *head2) {
  node *head = NULL, *l, *l1 = head1, *l2 = head2; // 结果，集合1，集合2
  int flag = 0;
  while (l1 != NULL && l2 != NULL) {
    char word;
    if (l1->word < l2->word) {
      word = l1->word;
      l1 = l1->next;
    } else if (l1->word > l2->word) {
      word = l2->word;
      l2 = l2->next;
    } else {
      word = l2->word;
      l2 = l2->next;
      l1 = l1->next;
    }
    if (flag) {
      node *t = new node;
      t->word = word;
      t->next = NULL;
      l->next = t;
      l = t;
    } else {
      head = new node;
      head->word = word;
      head->next = NULL;
      l = head;
      flag = 1;
    }
  }
  if (l1 == NULL && l2 != NULL) {
    swap(l1, l2);
  }
  while (l1 != NULL) {
    node *t = new node;
    t->word = l1->word;
    t->next = NULL;
    l->next = t;
    l = t;
    l1 = l1->next;
  }
  return head;
}

node *intersection(node *head1, node *head2) {
  node *head, *l, *l1 = head1, *l2 = head2; // 结果，集合1，集合2
  int flag = 0;
  while (l1 != NULL && l2 != NULL) {
    if (l1->word > l2->word) {
      swap(l1, l2);
    }
    while (l1 != NULL && l1->word < l2->word) { // 试图找到相等的
      l1 = l1->next;
    }
    // while (l2 != NULL && l2 ->word < l1 ->word) {
    //     l2 = l2->next;
    // }
    if (l1 != NULL && l1->word == l2->word) {
      if (flag) {
        node *t = new node;
        t->next = NULL;
        t->word = l1->word;
        l->next = t;
        l = t;
      } else {
        head = new node;
        head->word = l1->word;
        head->next = NULL;
        l = head;
        flag = 1;
      }
      l1 = l1->next;
      l2 = l2->next;
    }
  }
  return head;
}

node *diff(node *head1, node *inter) {
  node *l1 = head1, *head, *l, *l2 = inter;
  int flag = 0;
  while (l1 != NULL) {
    while (l1 != NULL && (l2 == NULL || l1->word < l2->word)) {
      if (flag) {
        node *t = new node;
        t->next = NULL;
        t->word = l1->word;
        l->next = t;
        l = t;
      } else {
        head = new node;
        head->word = l1->word;
        head->next = NULL;
        l = head;
        flag = 1;
      }
      l1 = l1->next;
    }
    if (l2 != NULL) {
      if (l1->word == l2->word) {
        l1 = l1->next;
      }
      l2 = l2->next;
    }
  }
  return head;
}

int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif // LOCAL
  node *a = read_set(), *b = read_set(), *inter;
  // print_set(a);
  print_set(sum(a, b));
  print_set(inter = intersection(a, b));
  print_set(diff(a, inter));
  return 0;
}