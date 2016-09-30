int N, matched[2 * MAXN], dist[2 * MAXN], pt[MAXN];
vector<int> g[MAXN];

bool bfs() {
  fill(dist, dist + 2 * N, -1);
  queue<int> q;
  REP (i, N) if (!matched[i]) {
    dist[i] = 0;
    q.push(i);
  }
  bool found = false;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (u > N && !matched[u]) found = true;
    if (u <= N) { // left side
      for (auto v : g[u])
        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
    } else if (u > N && matched[u]) { // right side
      if (dist[matched[u]] == -1) {
        dist[matched[u]] = dist[u] + 1;
        q.push(matched[u]);
      }
    }
  }
  return found;
}

bool dfs(int u) {
  for (int &i = pt[u]; i < g[u].size(); ++i) {
    int v = g[u][i];
    if (dist[v] == dist[u] + 1) {
      if (!matched[v] || (dist[matched[v]] == dist[v] + 1 && dfs(matched[v]))) {
        matched[v] = u;
        matched[u] = v;
        return true;
      }
    }
  }
  return false;
}

int hopcroft_karp() {
  int total = 0;
  while (bfs()) {
    fill(pt, pt + N, 0);
    REP (i, N)
      if (!matched[i])
        if (dfs(i)) ++total;
  }
  return total;
}
