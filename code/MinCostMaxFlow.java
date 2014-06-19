// Min cost max flow algorithm using an adjacency matrix.  If you
// want just regular max flow, setting all edge costs to 1 gives
// running time O(|E|^2 |V|).
//
// Running time: O(min(|V|^2 * totflow, |V|^3 * totcost))
//
// INPUT: cap -- a matrix such that cap[i][j] is the capacity of
//               a directed edge from node i to node j
//
//        cost -- a matrix such that cost[i][j] is the (positive)
//                cost of sending one unit of flow along a 
//                directed edge from node i to node j
//
//        source -- starting node
//        sink -- ending node
//
// OUTPUT: max flow and min cost; the matrix flow will contain
//         the actual flow values (note that unlike in the MaxFlow
//         code, you don't need to ignore negative flow values -- there
//         shouldn't be any)
//
// To use this, create a MinCostMaxFlow object, and call it like this:
//
//   MinCostMaxFlow nf;
//   int maxflow = nf.getMaxFlow(cap,cost,source,sink);

import java.util.*;

public class MinCostMaxFlow {
    boolean found[];
    int N, cap[][], flow[][], cost[][], dad[], dist[], pi[];
    
    static final int INF = Integer.MAX_VALUE / 2 - 1;
    
    boolean search(int source, int sink) {
	Arrays.fill(found, false);
	Arrays.fill(dist, INF);
	dist[source] = 0;

	while (source != N) {
	    int best = N;
	    found[source] = true;
	    for (int k = 0; k < N; k++) {
		if (found[k]) continue;
		if (flow[k][source] != 0) {
		    int val = dist[source] + pi[source] - pi[k] - cost[k][source];
		    if (dist[k] > val) {
			dist[k] = val;
			dad[k] = source;
		    }
		}
		if (flow[source][k] < cap[source][k]) {
		    int val = dist[source] + pi[source] - pi[k] + cost[source][k];
		    if (dist[k] > val) {
			dist[k] = val;
			dad[k] = source;
		    }
		}
		
		if (dist[k] < dist[best]) best = k;
	    }
	    source = best;
	}
	for (int k = 0; k < N; k++)
	    pi[k] = Math.min(pi[k] + dist[k], INF);
	return found[sink];
    }
    
    
    int[] getMaxFlow(int cap[][], int cost[][], int source, int sink) {
	this.cap = cap;
	this.cost = cost;
	
	N = cap.length;
        found = new boolean[N];
        flow = new int[N][N];
        dist = new int[N+1];
        dad = new int[N];
        pi = new int[N];
	
	int totflow = 0, totcost = 0;
	while (search(source, sink)) {
	    int amt = INF;
	    for (int x = sink; x != source; x = dad[x])
		amt = Math.min(amt, flow[x][dad[x]] != 0 ? flow[x][dad[x]] :
                       cap[dad[x]][x] - flow[dad[x]][x]);
	    for (int x = sink; x != source; x = dad[x]) {
		if (flow[x][dad[x]] != 0) {
		    flow[x][dad[x]] -= amt;
		    totcost -= amt * cost[x][dad[x]];
		} else {
		    flow[dad[x]][x] += amt;
		    totcost += amt * cost[dad[x]][x];
		}
	    }
	    totflow += amt;
	}
	
	return new int[]{ totflow, totcost };
    }
  
    public static void main (String args[]){
        MinCostMaxFlow flow = new MinCostMaxFlow();
        int cap[][] = {{0, 3, 4, 5, 0},
                       {0, 0, 2, 0, 0},
                       {0, 0, 0, 4, 1},
                       {0, 0, 0, 0, 10},
                       {0, 0, 0, 0, 0}};

        int cost1[][] = {{0, 1, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};

        int cost2[][] = {{0, 0, 1, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0}};
        
        // should print out:
        //   10 1
        //   10 3

        int ret1[] = flow.getMaxFlow(cap, cost1, 0, 4);
        int ret2[] = flow.getMaxFlow(cap, cost2, 0, 4);
        
        System.out.println (ret1[0] + " " + ret1[1]);
        System.out.println (ret2[0] + " " + ret2[1]);
    }
}
