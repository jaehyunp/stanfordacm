// Adjacency matrix implementation of Dinic's blocking flow algorithm.
//
// Running time:
//     O(|V|^4)
//
// INPUT: 
//     - graph, constructed using AddEdge()
//     - source
//     - sink
//
// OUTPUT:
//     - maximum flow value
//     - To obtain the actual flow, look at positive values only.

#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

const int INF = 1000000000;

struct MaxFlow {
  int N;
  VVI cap, flow;
  VI dad, Q;

  MaxFlow(int N) :
    N(N), cap(N, VI(N)), flow(N, VI(N)), dad(N), Q(N) {}

  void AddEdge(int from, int to, int cap) {
    this->cap[from][to] += cap;
  }

  int BlockingFlow(int s, int t) {
    fill(dad.begin(), dad.end(), -1);
    dad[s] = -2;

    int head = 0, tail = 0;
    Q[tail++] = s;
    while (head < tail) {
      int x = Q[head++];
      for (int i = 0; i < N; i++) {
        if (dad[i] == -1 && cap[x][i] - flow[x][i] > 0) {
          dad[i] = x;
          Q[tail++] = i;
        }
      }
    }

    if (dad[t] == -1) return 0;

    int totflow = 0;
    for (int i = 0; i < N; i++) {
      if (dad[i] == -1) continue;
      int amt = cap[i][t] - flow[i][t];
      for (int j = i; amt && j != s; j = dad[j])
        amt = min(amt, cap[dad[j]][j] - flow[dad[j]][j]);
      if (amt == 0) continue;
      flow[i][t] += amt;
      flow[t][i] -= amt;
      for (int j = i; j != s; j = dad[j]) {
        flow[dad[j]][j] += amt;
        flow[j][dad[j]] -= amt;
      }
      totflow += amt;
    }

    return totflow;
  }

  int GetMaxFlow(int source, int sink) {
    int totflow = 0;
    while (int flow = BlockingFlow(source, sink))
      totflow += flow;
    return totflow;
  }
};

int main() {

  MaxFlow mf(5);
  mf.AddEdge(0, 1, 3);
  mf.AddEdge(0, 2, 4);
  mf.AddEdge(0, 3, 5);
  mf.AddEdge(0, 4, 5);
  mf.AddEdge(1, 2, 2);
  mf.AddEdge(2, 3, 4);
  mf.AddEdge(2, 4, 1);
  mf.AddEdge(3, 4, 10);
    
  // should print out "15"
  cout << mf.GetMaxFlow(0, 4) << endl;
}

// BEGIN CUT
// The following code solves SPOJ problem #203: Potholers (POTHOLE)

#ifdef COMMENT
int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int n;
    cin >> n;
    MaxFlow mf(n);
    for (int j = 0; j < n-1; j++) {
      int m;
      cin >> m;
      for (int k = 0; k < m; k++) {
        int p;
        cin >> p;
	p--;
        int cap = (j == 0 || p == n-1) ? 1 : INF;
	mf.AddEdge(j, p, cap);
      }
    }

    cout << mf.GetMaxFlow(0, n-1) << endl;
  }
  return 0;
}
#endif

// END CUT
