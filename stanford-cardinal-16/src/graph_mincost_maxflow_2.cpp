typedef pair<int, int> ii;
struct edge { int u, v, cost, cap, flow; } E[MAXE], * pred[MAXN];
vector<edge *> g[MAXN];
int N, M, EE, dist[MAXN], phi[MAXN];

inline edge * opp(edge * e) { return E + ((e - E) ^ 1); }

void add_edge(int u, int v, int cost, int cap) {
  E[EE] = { u, v, cost, cap, 0 };
  g[u].emplace_back(E + (EE++));
  E[EE] = { v, u, -cost, 0, 0 };
  g[v].emplace_back(E + (EE++));
}

bool dijkstra(int S, int T) {
  fill(dist, dist + N, INF);
  fill(pred, pred + N, nullptr);
  priority_queue<ii, vector<ii>, greater<ii>> pq;
  dist[S] = 0;
  for (pq.emplace(dist[S], S); !pq.empty(); ) {
    int u = pq.top().second; pq.pop();
    for (auto e : g[u]) {
      if (e->cap - e->flow > 0 &&
          dist[e->v] > dist[e->u] + e->cost + phi[e->u] - phi[e->v]) {
        dist[e->v] = dist[e->u] + e->cost + phi[e->u] - phi[e->v];
        pred[e->v] = e;
        pq.emplace(dist[e->v], e->v);
      }
    }
  }
  FOR (i, N) phi[i] = min(INF, phi[i] + dist[i]);
  return dist[T] != INF;
}

pair<int, int> mincost_maxflow(int S, int T) {
  int mincost = 0, maxflow = 0;
  fill(phi, phi + N, 0);
  while (dijkstra(S, T)) {
    int flow = INF;
    for (edge * e = pred[T]; e; e = pred[e->u])
      flow = min(flow, e->cap - e->flow);
    for (edge * e = pred[T]; e; e = pred[e->u]) {
      mincost += e->cost * flow;
      e->flow += flow;
      opp(e)->flow -= flow;
    }
    maxflow += flow;
  }
  return make_pair(mincost, maxflow);
}
