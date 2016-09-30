struct node {
  int s, e, num_children;
  node * parent, * link, * children[26];
  inline int length(int ee) { return min(e, ee) - s; }
  node * get(char x) { return children[x - 'a']; }
  void set(char x, node * u) {
    if (children[x - 'a'] != NULL) {
      --num_children;
      children[x - 'a']->parent = NULL;
    }
    children[x - 'a'] = u;
    if (u != NULL) {
      ++num_children;
      u->parent = this;
    }
  }
} pool[5 * MAXN];
int n_pool;

node * get_node(int s, int e = INF) {
  node * x = pool + (n_pool++);
  x->s = s;
  x->e = e;
  x->parent = NULL;
  x->link = NULL;
  memset(x->children, 0, sizeof x->children);
  x->num_children = 0;
  return x;
}

struct ukkonen {
  const char * S;
  int pos, head;
  node * root, * cur;

  long long total_length;
  queue<node *> leaves;

  ukkonen(const char * S): S(S), pos(0), head(0), total_length(0) {
    cur = root = get_node(0, 0);
  }

  void traverse(int e) {
    while (node * u = cur->get(S[head])) {
      if (e - head <= u->length(e)) break;
      head += u->length(e);
      cur = u;
    }
  }

  void follow_link() {
    if (cur->e == 0) ++head;
    else cur = cur->link;
  }

  node * split(node * u, int d) {
    node * p = u->parent;
    p->set(S[head], NULL);
    node * v = get_node(u->s, u->s + d);
    u->s += d;
    p->set(S[head], v);
    v->set(S[u->s], u);
    return v;
  }

  void extend() {
    total_length += leaves.size();
    for (node * last = NULL; head <= pos; ) {
      traverse(pos + 1);
      if (node * u = cur->get(S[head])) {
        int window = pos - head;
        if (S[pos] == S[u->s + window]) {
          if (last) last->link = cur;
          break;
        } else {
          node * v = split(u, window);
          node * w = get_node(pos);
          v->set(S[pos], w);
          leaves.emplace(w);
          ++total_length;
          if (last) last->link = v;
          last = v;
        }
      } else {
        node * v = get_node(pos);
        cur->set(S[head], v);
        leaves.emplace(v);
        ++total_length;
        if (last) last->link = cur;
        last = NULL;
      }
      follow_link();
    }
    ++pos;
  }

  node * delete_leaf(node * leaf) {
    node * p = leaf->parent;
    total_length -= leaf->length(pos);
    p->set(S[leaf->s], NULL);
    return p;
  }

  void trim() {
    traverse(pos);
    node * leaf = leaves.front(); leaves.pop();
    node * u = (pos - head == 0) ? cur : cur->get(S[head]);
    while (leaf->num_children == 0 && leaf != u)
      leaf = delete_leaf(leaf);
    if (leaf == u && pos - head != 0 && u->num_children == 0) {
      split(u, pos - head);
      leaf = delete_leaf(leaf);
      traverse(pos);
    }
    if (leaf->e != 0 && leaf->num_children == 0) {
      leaves.emplace(leaf);
      leaf->s = pos - leaf->length(pos);
      leaf->e = INF;
      follow_link();
    }
  }
};
