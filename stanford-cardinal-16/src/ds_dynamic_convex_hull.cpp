bool query_flag = false;
struct line {
  long long m, c;
  mutable function<const line*()> succ;
  bool operator<(const line& o) const {
    if (!query_flag) return m < o.m;
    const line* s = succ();
    if (!s) return false;
    return (c - s->c) < (s->m - m) * o.m;
  }
};

struct maximum_hull : multiset<line> {
  bool bad(iterator y) {
    auto x = (y == begin()) ? end() : prev(y), z = next(y);
    if (x == end() && z == end()) return false;
    else if (x == end()) return y->m == z->m && y->c <= z->c;
    else if (z == end()) return y->m == x->m && y->c <= x->c;
    else return (x->c - y->c) * (z->m - y->m) >= (y->c - z->c) * (y->m - x->m);
  }
  void insert_line(const long long& m, const long long& c) {
    auto y = insert({ m, c, nullptr });
    y->succ = [=] { return next(y) == end() ? nullptr : &*next(y); };
    if (bad(y)) { erase(y); return; }
    iterator z;
    while ((z = next(y)) != end() && bad(z)) erase(z);
    while (y != begin() && bad(z = prev(y))) erase(z);
  }
  long long eval(long long x) {
    if (empty()) return numeric_limits<ll>::min();
    query_flag = true;
    auto l = *lower_bound({ x, 0, nullptr });
    query_flag = false;
    return l.m * x + l.c;
  }
};
