void dfs(int u, int p = 0) {
  size[u] = 1;
  parent[u] = p;
  for (auto v : g[u]) if (v != p) {
    depth[v] = depth[u] + 1;
    dfs(v, u);
    size[u] += size[v];
    if (!hld_child[u] || size[hld_child[u]] < size[v])
      hld_child[u] = v;
  }
}

// gives a 1-index to each node such that indices
// in each heavy path are contiguous
void hld(int u, int p = 0) {
  static int index = 0;
  hld_index[u] = ++index;
  hld_order[hld_index[u]] = X[u];
  if (!hld_root[u]) hld_root[u] = u;
  if (hld_child[u]) {
    hld_root[hld_child[u]] = hld_root[u];
    hld(hld_child[u], u);
  }
  for (auto v : g[u]) if (v != p && v != hld_child[u])
    hld(v, u);
}

// perform a query the path betwwen a and b,
// where query_path is a function on ranges of hld indices
void hld_query(int a, int b) {
  int a_value = 0, b_value = 0;

  while (hld_root[a] != hld_root[b]) {
    if (depth[hld_root[a]] < depth[hld_root[b]]) {
      b_value += query_path(hld_index[hld_root[b]], hld_index[b]);
      b = parent[hld_root[b]];
    } else {
      a_value += query_path(hld_index[hld_root[a]], hld_index[a]);
      a = parent[hld_root[a]];
    }
  }
  if (depth[a] < depth[b])
    b_value += query_path(hld_index[a], hld_index[b]);
  else
    a_value += query_path(hld_index[b], hld_index[a]);

  return a_value + b_value;
}
