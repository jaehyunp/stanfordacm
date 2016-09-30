typedef int value;

enum { LEFT, RIGHT };
struct node {
  int size, priority;
  value x, subtree;
  node *child[2];
  node(const value &x): size(1), x(x), subtree(x) {
    priority = rand();
    child[0] = child[1] = nullptr;
  }
};

inline int size(const node *a) { return a == nullptr ? 0 : a->size; }

inline void update(node *a) {
  if (a == nullptr) return;
  a->size = size(a->child[0]) + size(a->child[1]) + 1;
  a->subtree = a->x;
  if (a->child[LEFT] != nullptr) a->subtree = a->child[LEFT]->subtree + a->subtree;
  if (a->child[RIGHT] != nullptr) a->subtree = a->subtree + a->child[RIGHT]->subtree;
}

node *rotate(node *a, bool d) {
  node *b = a->child[d];
  a->child[d] = b->child[!d];
  b->child[!d] = a;
  update(a); update(b);
  return b;
}

node *insert(node *a, int index, const value &x) {
  if (a == nullptr && index == 0) return new node(x);
  int middle = size(a->child[LEFT]);
  bool dir = index > middle;
  if (!dir) a->child[LEFT]  = insert(a->child[LEFT], index, x);
  else      a->child[RIGHT] = insert(a->child[RIGHT], index - middle - 1, x);
  update(a);
  if (a->priority > a->child[dir]->priority) a = rotate(a, dir);
  return a;
}

node *erase(node *a, int index) {
  assert(a != nullptr);
  int middle = size(a->child[LEFT]);
  if (index == middle) {
    if (a->child[LEFT] == nullptr && a->child[RIGHT] == nullptr) {
      delete a;
      return nullptr;
    } else if (a->child[LEFT] == nullptr) a = rotate(a, RIGHT);
    else if (a->child[RIGHT] == nullptr) a = rotate(a, LEFT);
    else a = rotate(a, a->child[LEFT]->priority < a->child[RIGHT]->priority);
    a = erase(a, index);
  } else {
    bool dir = index > middle;
    if (!dir) a->child[LEFT] = erase(a->child[LEFT], index);
    else      a->child[RIGHT] = erase(a->child[RIGHT], index - middle - 1);
  }
  update(a);
  return a;
}

void modify(node *a, int index, const value &x) {
  assert(a != nullptr);
  int middle = size(a->child[LEFT]);
  if (index == middle) a->x = x;
  else {
    bool dir = index > middle;
    if (!dir) modify(a->child[LEFT], index, x);
    else      modify(a->child[RIGHT], index - middle - 1, x);
  }
  update(a);
}

value query(node *a, int l, int r) {
  assert(a != nullptr);
  if (l <= 0 && size(a) - 1 <= r) return a->subtree;
  int middle = size(a->child[LEFT]);
  if (r < middle) return query(a->child[LEFT], l, r);
  if (middle < l) return query(a->child[RIGHT], l - middle - 1, r - middle - 1);
  value res = a->x;
  if (l < middle && a->child[LEFT] != nullptr)
    res = query(a->child[LEFT], l, r) + res;
  if (middle < r && a->child[RIGHT] != nullptr)
    res = res + query(a->child[RIGHT], l - middle - 1, r - middle - 1);
  return res;
}
