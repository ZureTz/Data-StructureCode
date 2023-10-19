#include <iostream>
using std::cout;

struct sNode {
  int num;
  char chdata;
  sNode *nextJump; // not average 'next'(link to before)
  sNode *succData; // point to the value after

  sNode(char ch, sNode *nextjmp = nullptr, sNode *succdta = nullptr)
      : chdata(ch), succData(succdta), nextJump(nextjmp) {}
} *head = new sNode(0);

void construct(sNode *const head, const char *srcStr) {
  int num = 0;
  head->num = num++;
  sNode *temp = head;
  while (*srcStr) {
    // temp->linkNext(new sNode(*srcStr));
    temp->succData = new sNode(*srcStr, temp);
    temp->succData->num = num++;
    temp = temp->succData;
    srcStr++;
  }
}

void genNext(sNode *const strHead) {
  sNode *fast = strHead->succData;
  if (!fast) {
    return;
  }
  while (fast->succData) {
    sNode *temp = fast;
    while (temp->nextJump) {
      cout << temp->num << ' ' << temp->chdata <<' ' << fast->num << ' '
           << fast->chdata << '\n';
      if (temp->nextJump->chdata == fast->chdata) {
        fast->succData->nextJump = temp->nextJump->succData;
        break;
      }
      temp = temp->nextJump;
    }
    if (temp->nextJump == nullptr) {
      fast->succData->nextJump = head->succData;
    }
    fast = fast->succData;
  }
}

std::ostream &operator<<(std::ostream &os, const sNode *const head) {
  sNode *temp = head->succData;
  while (temp) {
    os << temp->num << ' ';
    os.put(temp->chdata);
    os << ' ' << temp->nextJump->num << std::endl;
    temp = temp->succData;
  }
  return os;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);

  const char *str = "abcabaa";
  construct(head, str);
  cout << head << std::endl;
  genNext(head);
  cout << head;

  return 0;
}