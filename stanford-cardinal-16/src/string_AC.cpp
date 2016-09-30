struct AC {
  int N, P;
  vector<map<char, int>> next; // trie
  vector<vector<int>> next; // automaton
  vector<int> link, out_link;
  vector<vector<int>> out;
  AC(): N(0), P(0) { node(); }
  int node() {
    next.emplace_back(); // trie
    next.emplace_back(26, 0); // automaton
    link.emplace_back(0);
    out_link.emplace_back(0);
    out.emplace_back(0);
    return N++;
  }
  int add_pattern(const string T) {
    int u = 0;
    for (auto c : T) {
      // trie
      if (!next[u][c]) next[u][c] = node();
      u = next[u][c];
      // automaton
      if (!next[u][c - 'a']) next[u][c - 'a'] = node();
      u = next[u][c - 'a'];
    }
    out[u].push_back(P);
    return P++;
  }
  void compute() {
    queue<int> q;
    for (q.push(0); !q.empty(); ) {
      int u = q.front(); q.pop();
      // trie:
      for (auto e : next[u]) {
        int v = e.second;
        link[v] = u ? advance(link[u], e.first) : 0;
        out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
        q.push(e.second);
      }
      // automaton:
      for (int c = 0; c < 26; ++c) {
        int v = next[u][c];
        if (!v) next[u][c] = next[link[u]][c];
        else {
          link[v] = u ? next[link[u]][c] : 0;
          out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
          q.push(v);
        }
      }
    }
  }
  int advance(int u, char c) {
    // trie:
    while (u && next[u].find(c) == next[u].end())
      u = link[u];
    if (next[u].find(c) != next[u].end())
      u = next[u][c];
    // automaton:
    while (u && !next[u][c - 'a']) u = link[u];
    u = next[u][c - 'a'];
    return u;
  }
  void match(const string S) {
    int u = 0;
    for (auto c : S) {
      u = advance(u, c);
      for (int v = u; v; v = out_link[v])
        for (auto p : out[v])
          cout << "match " << p << endl;
    }
  }
};
