#include <cstddef>
#include <iostream>
#include <ostream>

struct sNode {
  char ch;
  sNode *prev;
  sNode *next;
  explicit sNode(const char ch, sNode *prev = nullptr, sNode *next = nullptr)
      : ch(ch), prev(prev), next(next) {}

  inline void linkNext(sNode *nextNode) {
    this->next = nextNode;
    nextNode->prev = this;
  }

  inline void linkNextPrev(sNode *prevNode) {
    this->prev = prevNode;
    prevNode->next = this;
  }
};

struct LString {
  sNode *const head = new sNode(0);

  LString() {}
  LString(const char *str) { assign(str); }
  LString(const LString &rhs) {
    sNode *temp = head;
    sNode *rhsTemp = rhs.head->next;
    while (rhsTemp) {
      temp->linkNext(new sNode(rhsTemp->ch));
      temp = temp->next;
      rhsTemp = rhsTemp->next;
    }
  }

  void assign(const char *srcStr) {
    sNode *temp = head;
    while (*srcStr) {
      temp->linkNext(new sNode(*srcStr));
      temp = temp->next;
      srcStr++;
    }
  }

  // LString &operator=(const LString &rhs) {
  //   sNode *temp = head;
  //   sNode *rhsTemp = rhs.head->next;
  //   while (rhsTemp) {
  //     temp->linkNext(new sNode(rhsTemp->ch));
  //     temp = temp->next;
  //     rhsTemp = rhsTemp->next;
  //   }
  //   return *this;
  // }
  void copy(const LString &rhs) {
    sNode *temp = head;
    sNode *rhsTemp = rhs.head->next;
    while (rhsTemp) {
      temp->linkNext(new sNode(rhsTemp->ch));
      temp = temp->next;
      rhsTemp = rhsTemp->next;
    }
  }

  // bool operator==(const LString &rhs) {
  //   sNode *lhsTemp = head->next;
  //   sNode *rhsTemp = rhs.head->next;

  //   while (lhsTemp && rhsTemp) {
  //     if (lhsTemp->ch != rhsTemp->ch) {
  //       return false;
  //     }
  //     lhsTemp = lhsTemp->next;
  //     rhsTemp = rhsTemp->next;
  //   }
  //   // checked before and both of them is nullptr
  //   if (lhsTemp == rhsTemp) {
  //     return true;
  //   }
  //   return false;
  // }
  bool compare(const LString &rhs) {
    sNode *lhsTemp = head->next;
    sNode *rhsTemp = rhs.head->next;

    while (lhsTemp && rhsTemp) {
      if (lhsTemp->ch != rhsTemp->ch) {
        return false;
      }
      lhsTemp = lhsTemp->next;
      rhsTemp = rhsTemp->next;
    }
    // checked before and both of them is nullptr
    if (lhsTemp == rhsTemp) {
      return true;
    }
    return false;
  }

  size_t length() {
    size_t count = 0;
    sNode *temp = head->next;
    while (temp) {
      count++;
      temp = temp->next;
    }
    return count;
  }
};

LString concat(const LString &lhs, const LString &rhs) {
  LString result;
  sNode *temp = result.head;
  sNode *lhsTemp = lhs.head->next;
  while (temp && lhsTemp) {
    temp->linkNext(new sNode(lhsTemp->ch));
    temp = temp->next;
    lhsTemp = lhsTemp->next;
  }
  sNode *rhsTemp = rhs.head->next;
  while (temp && rhsTemp) {
    temp->linkNext(new sNode(rhsTemp->ch));
    temp = temp->next;
    rhsTemp = rhsTemp->next;
  }
  return result;
}

LString substr(const LString &src, size_t index, size_t length) {
  sNode *srcTemp = src.head->next;
  while (index-- > 0) {
    srcTemp = srcTemp->next;
  }

  LString result;
  sNode *resTemp = result.head;
  while (srcTemp && length-- > 0) {
    resTemp->linkNext(new sNode(srcTemp->ch));
    resTemp = resTemp->next;
    srcTemp = srcTemp->next;
  }
  return result;
}

// output
std::ostream &operator<<(std::ostream &os, const LString &rhs) {
  sNode *temp = rhs.head->next;
  while (temp) {
    os.put(temp->ch);
    temp = temp->next;
  }
  return os;
}

int main(int argc, char const *argv[]) {
  std::ios::sync_with_stdio(false);
  LString str1 = "hello";
  LString str2 = "world";
  std::cout << str1 << str2 << std::endl;
  auto str3 = concat(str1, str2);
  std::cout << str3.length() << std::endl;
  std::cout << substr(str3, 1, 7) << std::endl;
  LString str4 = "helussahfiausghdfsadfasgasgrldl";
  std::cout << (str3.compare(str4) ? "true" : "false") << std::endl;
  str3.copy(str4);
  std::cout << str3 << std::endl;
  return 0;
}
