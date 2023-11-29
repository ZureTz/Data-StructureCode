#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
struct node {
  int coef; // 系数
  int expn; // 指数
  node *next;
};

node *creat_list(int n) { // 读入链表
  node *head, *r;
  head = new node;
  r = head;
  int coef, expn;
  std::string str;
  std::getline(cin, str);
  std::stringstream ss(str);
  while (n--) {
    while (!isdigit(ss.peek()) && !(ss.peek() == '-')) {
      ss.get();
    }
    ss >> coef;

    while (!isdigit(ss.peek()) && !(ss.peek() == '-')) {
      ss.get();
    }
    ss >> expn;
    if (coef == 0) {
      continue;
    }
    node *tmp = new node; // 创建临时结点
    tmp->coef = coef;
    tmp->expn = expn;
    r->next = tmp; // 临时结点接到链表中
    r = tmp;
  }
  r->next = NULL; // 结尾设为 NULL
  return head;
}

node *add_list(node *a, node *b) {
  node *r, *fans, *ans;
  node *ha,
      *hb; // 为了防止修改指针本身的值，使用代理指针来完成操作，也就是游标。
  fans = new node;
  ans = fans; // ans 作为fans 的”游标“
  ha = a->next;
  hb = b->next;
  while (ha && hb) {
    node *tmp = new node; // 建立一次即可
    if (ha->expn > hb->expn) { // 每次把指数（exponent）较大的加入链表fans
      tmp->coef = ha->coef;
      tmp->expn = ha->expn;
      ans->next = tmp;
      ans = tmp;
      ha = ha->next;
    } else if (ha->expn < hb->expn) {
      tmp->coef = hb->coef;
      tmp->expn = hb->expn;
      ans->next = tmp;
      ans = tmp;
      hb = hb->next;
    } else {
      int mulOfcoef = (ha->coef) + (hb->coef); // 如果指数相同， 就把系数求和。
      if (mulOfcoef != 0) {
        tmp->coef = mulOfcoef;
        tmp->expn = ha->expn;
        ans->next = tmp;
        ans = tmp;
      }
      ha = ha->next; // 注意这里 即使和为0 ，也要移动“游标”
      hb = hb->next;
    }
  }
  while (ha) {
    node *tmp = new node;
    tmp->coef = ha->coef;
    tmp->expn = ha->expn;
    ans->next = tmp;
    ans = tmp;
    ha = ha->next;
  }
  while (hb) {
    node *tmp = new node;
    tmp->coef = hb->coef;
    tmp->expn = hb->expn;
    ans->next = tmp;
    ans = tmp;
    hb = hb->next;
  }
  ans->next = NULL; // 结尾设为 NULL
  return fans;
}
void print_list(node *l) {
  node *hc;
  int flag = 0;
  hc = l->next; // 指针操作常用，用新创立的节点代替源节点操作
  if (hc == NULL) { // 格式控制 。。 真坑！
    printf("0 0");
  }
  printf("%d %d", hc->coef, hc->expn);
  hc = hc->next;
  while (hc != NULL) {
    printf(",%d %d", hc->coef, hc->expn);
    hc = hc->next;
  }
  printf("\n");
}
int main() {
#ifdef LOCAL
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif // LOCAL
  int n, m;
  scanf("%d%d", &n, &m);
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  node *a = creat_list(n);
  node *b = creat_list(m);
  node *c = add_list(a, b);
  print_list(c);
  return 0;
}