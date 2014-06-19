#include <iostream>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;

typedef double T;
typedef vector<T> VT;
typedef vector<VT> VVT;

typedef vector<int> VI;
typedef vector<VI> VVI;

// This function runs Dijkstra's algorithm for single source
// shortest paths.  No negative cycles allowed!
//
// Running time: O(|V|^2)
//
//   INPUT:   start, w[i][j] = cost of edge from i to j
//   OUTPUT:  dist[i] = min weight path from start to i
//            prev[i] = previous node on the best path from the
//                      start node   

void Dijkstra (const VVT &w, VT &dist, VI &prev, int start){
  int n = w.size();
  VI found (n);
  prev = VI(n, -1);
  dist = VT(n, 1000000000);
  dist[start] = 0;
  
  while (start != -1){
    found[start] = true;
    int best = -1;
    for (int k = 0; k < n; k++) if (!found[k]){
      if (dist[k] > dist[start] + w[start][k]){
        dist[k] = dist[start] + w[start][k];
        prev[k] = start;
      }
      if (best == -1 || dist[k] < dist[best]) best = k;
    }
    start = best;    
  }
}

// This function runs the Floyd-Warshall algorithm for all-pairs
// shortest paths.  Also handles negative edge weights.  Returns true
// if a negative weight cycle is found.
//
// Running time: O(|V|^3)
//
//   INPUT:  w[i][j] = weight of edge from i to j
//   OUTPUT: w[i][j] = shortest path from i to j
//           prev[i][j] = node before j on the best path starting at i

bool FloydWarshall (VVT &w, VVI &prev){
  int n = w.size();
  prev = VVI (n, VI(n, -1));
  
  for (int k = 0; k < n; k++){
    for (int i = 0; i < n; i++){
      for (int j = 0; j < n; j++){
        if (w[i][j] > w[i][k] + w[k][j]){
          w[i][j] = w[i][k] + w[k][j];
          prev[i][j] = k;
        }
      }
    }
  }
 
  // check for negative weight cycles
  for(int i=0;i<n;i++)
    if (w[i][i] < 0) return false;
  return true;
}