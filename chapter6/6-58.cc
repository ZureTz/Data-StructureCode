enum PtrTag { Link, Thread };
template <typename T> struct BiThrNode {
  using NodePtr = BiThrNode<T> *;

  T data;
  NodePtr left;
  NodePtr right;
  PtrTag LTag, RTag;

  BiThrNode<T>(T data = T(), NodePtr left = nullptr, NodePtr right = nullptr)
      : data(data), left(left), right(right),
        LTag(left ? PtrTag::Link : PtrTag::Thread),
        RTag(right ? PtrTag::Link : PtrTag::Thread) {}
};

template <typename T> void connect(BiThrNode<T> *p, BiThrNode<T> *x) {
  if (p->LTag == PtrTag::Link && p->RTag == PtrTag::Link) {
    return;
  }

  if (p->LTag == PtrTag::Thread) {
    p->LTag = PtrTag::Link;
    p->left = x;

    BiThrNode<T> *temp = x;
    while (temp->right) {
      temp = temp->right;
    }
    temp->RTag = PtrTag::Link;
    temp->right = p;

    return;
  }

  // root->RTag == PtrTag::Thread
  p->RTag = PtrTag::Link;
  p->right = x;

  BiThrNode<T> *temp = x;
  while (temp->left) {
    temp = temp->left;
  }
  temp->LTag = PtrTag::Link;
  temp->left = p;
}