typedef pair<int, int> ii;
struct edge { int u, v, cap, flow; } E[MAXE];
vector<edge *> g[MAXN];
int N, EE, dist[MAXN], pt[MAXN];

inline edge * opp(edge * e) { return E + ((e - E) ^ 1); }

void add_edge(int u, int v, int cap) {
  E[EE] = { u, v, cap, 0 };
  g[u].emplace_back(E + (EE++));
  E[EE] = { v, u, 0, 0 };
  g[v].emplace_back(E + (EE++));
}

bool bfs(int S, int T) {
  queue<int> q;
  fill(dist, dist + N, INF);
  dist[S] = 0;
  for (q.emplace(S); !q.empty(); ) {
    int u = q.front(); q.pop();
    if (u == T) break;
    for (auto e : g[u]) {
      if (e->cap - e->flow > 0 && dist[e->v] > dist[e->u] + 1) {
        dist[e->v] = dist[e->u] + 1;
        q.emplace(e->v);
      }
    }
  }
  return dist[T] != INF;
}

int dfs(int u, int T, int flow = INF) {
  if (u == T || flow == 0) return flow;
  for (int &i = pt[u]; i < g[u].size(); ++i) {
    edge * e = g[u][i];
    if (dist[e->v] == dist[e->u] + 1) {
      if (int pushed = dfs(e->v, T, min(e->cap - e->flow, flow))) {
        e->flow += pushed;
        opp(e)->flow -= pushed;
        return flow;
      }
    }
  }
  return 0;
}

int dinic(int S, int T) {
  int maxflow = 0;
  while (bfs(S, T)) {
    fill(pt, pt + N, 0);
    while (int flow = dfs(S, T))
      maxflow += flow;
  }
  return maxflow;
}
