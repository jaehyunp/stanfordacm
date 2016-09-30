typedef int value;

enum { LEFT, RIGHT };
struct node {
  node * child[2], * parent;
  value v, subtree;
  int size;
} pool[MAXN], * pool_next = pool;

node * allocate(const value & v) {
  node * x = pool_next++;
  x->parent = x->child[LEFT] = x->child[RIGHT] = nullptr;
  x->subtree = x->v = v;
  x->size = 1;
  return x;
}

struct tree {
  node * root;
  tree(): root(allocate(0)) {}

  bool child_dir(const node * x, const node * y) { return (x->child[LEFT] == y) ? LEFT : RIGHT; }
  bool is_child(const node * x, const node * y) { return x->child[LEFT] == y || x->child[RIGHT] == y; }

  void update(node * x) {
    x->size = 1;
    x->subtree = x->v;
    FOR (d, 2) if (x->child[d] != nullptr) {
      x->size += x->child[d]->size;
      if (d == LEFT) x->subtree = x->child[LEFT]->subtree + x->subtree;
      else x->subtree = x->subtree + x->child[RIGHT]->subtree;
    }
  }

  void set_child(node * x, bool dir, node * y) {
    if ((x->child[dir] = y) != nullptr) y->parent = x;
    update(x);
  }

  node * rotate(node * x, bool dir) {
    node * parent = x->parent, * y = x->child[dir];
    set_child(x, dir, y->child[!dir]);
    set_child(y, !dir, x);
    set_child(parent, child_dir(parent, x), y);
    return y;
  }

  node * splay(node * x) {
    node * old_p = nullptr;
    while (x->parent != nullptr) {
      node * p = x->parent;
      x = rotate(p, child_dir(p, x));
      if (old_p != nullptr && is_child(p, old_p)) rotate(p, child_dir(p, old_p));
      old_p = p;
    }
    return x;
  }

  node * insert(int order, const value & v) { // order is 0-indexed
    bool dir = LEFT;
    node * parent = root, * x = parent->child[LEFT];
    while (x != nullptr) {
      int left_size = (x->child[LEFT] == nullptr) ? 0 : x->child[LEFT]->size;
      parent = x;
      if (order <= left_size) x = x->child[dir = LEFT];
      else {
        order -= left_size + 1;
        x = x->child[dir = RIGHT];
      }
    }
    set_child(parent, dir, x = allocate(v));
    return splay(x);
  }

  node * find(int order) {
    node * x = root->child[LEFT];
    while (true) {
      int left_size = (x->child[LEFT] == nullptr) ? 0 : x->child[LEFT]->size;
      if (order < left_size) x = x->child[LEFT];
      else if (order == left_size) break;
      else {
        order -= left_size + 1;
        x = x->child[RIGHT];
      }
    }
    return splay(x);
  }

  void erase(const int& order) {
    node * x = find(order);
    if (x->child[LEFT] == nullptr) set_child(root, LEFT, x->child[RIGHT]);
    else if (x->child[RIGHT] == nullptr) set_child(root, LEFT, x->child[LEFT]);
    else {
      node * y = x->child[RIGHT];
      while (y->child[LEFT] != nullptr) y = y->child[LEFT];
      y = splay(y);
      set_child(y, LEFT, x->child[LEFT]);
      set_child(root, LEFT, y);
    }
  }

  value query(int e) { // e is the prefix length desired.
    node * x = root->child[LEFT];
    if (e <= 0) return 0;
    if (e >= x->size) return x->subtree;
    x = find(e - 1);
    if (x->child[LEFT] != nullptr) return x->child[LEFT]->subtree * x->v;
    else return x->v;
  }
};
