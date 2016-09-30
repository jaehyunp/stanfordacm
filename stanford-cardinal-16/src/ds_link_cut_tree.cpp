enum { LEFT, RIGHT };

struct node {
  node * parent, * child[2];
  int value, subtree_value;
  bool flip;

  void update(bool change = false, int new_value = 0) {
    if (change) value = new_value;
    subtree_value = value;
    FOR (d, 2) if (child[d] != nullptr) subtree_value += child[d]->subtree_value;
  }

  void propagate() {
    if (!flip) return;
    swap(child[LEFT], child[RIGHT]);
    FOR (d, 2) if (child[d] != nullptr) child[d]->flip ^= 1;
    flip = false;
  }

  void set_child(bool d, node * x) {
    if ((child[d] = x) != nullptr) x->parent = this;
    update();
  }

  bool has_child(node * x) { return child[LEFT] == x || child[RIGHT] == x; }
  bool is_root() { return parent == nullptr || !parent->has_child(this); }
  bool child_direction(node * x) { return (child[LEFT] == x) ? LEFT : RIGHT; }

  void rotate() {
    node *g = parent->parent;

    if (g != nullptr) g->propagate();
    parent->propagate();
    this->propagate();

    bool d = parent->child_direction(this);
    parent->set_child(d, child[!d]);
    this->set_child(!d, parent);
    if (g == nullptr || !g->has_child(parent)) parent = g;
    else g->set_child(g->child_direction(parent), this);
  }

  node * splay() {
    while (!is_root()) {
      node * p = parent;
      rotate();
      if (!is_root()) rotate();
      if (has_child(p->parent)) p->rotate();
    }
    return this;
  }

  node * leftmost_child() {
    for (node * x = this; ; x = x->child[LEFT]) {
      x->propagate();
      if (x->child[LEFT] == nullptr)
        return x->splay();
    }
  }
} nodes[MAXN];

node * expose(node * v) {
  node * old_preferred = nullptr;
  for (node * x = v; x != nullptr; x = x->parent) {
    x->splay()->propagate();
    x->set_child(RIGHT, old_preferred);
    old_preferred = x;
  }
  return v->splay();
}

void reroot(node * v) {
  expose(v)->flip ^= 1;
  v->parent = nullptr;
}

node * find_root(node * v) {
  return expose(v)->leftmost_child();
}

bool connected(node * u, node * v) {
  expose(u);
  return expose(v)->parent != nullptr;
}

bool link(node * u, node * v) {
  if (find_root(u) == find_root(v)) return false;
  reroot(v);
  v->parent = u;
  return true;
}

bool cut(node * u, node * v) {
  reroot(u);
  expose(v);
  if (v->child[RIGHT] != u || u->child[LEFT] != nullptr) return false;
  v->child[RIGHT]->parent = nullptr;
  v->child[RIGHT] = nullptr;
}

int query(node * u, node * v) {
  if (find_root(u) != find_root(v)) return -1;
  reroot(u);
  return expose(v)->subtree_value;
}
