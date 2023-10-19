enum var { x, y, z };
struct MPNode {
  bool tag;
  int exp;
  union {
    float coef;
    MPNode *hp; // head ptr
  };
  MPNode *tp; // table ptr
};

void partDerivative(MPNode *const head) {
  if (head->exp == 3) {
    partDerivative(head->hp);
    return;
  }

  MPNode *ptr = head;
  if (head->exp == var::x) {
    while (ptr->tp) {
      if (ptr->tp->exp == 0) {
        ptr->tp = nullptr;
        break;
      }
      ptr->tp->coef *= (ptr->tp->exp--);
    }
    return;
  }
  // head->exp != x
  while (ptr->tp) {
    if (ptr->tp->tag == false) {
      if (ptr->tp->exp == 0 || ptr->tp->tp == nullptr) {
        ptr->tp = nullptr;
        break;
      }
      // else has exp
      ptr->tp = ptr->tp->tp;
      continue;
    }
    // if ptr->tag == true // table
    partDerivative(ptr->tp->hp);
    ptr = ptr->tp;
  }
}