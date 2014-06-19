struct Edge;
typedef list<Edge>::iterator iter;

struct Edge
{
	int next_vertex;
	iter reverse_edge;

	Edge(int next_vertex)
		:next_vertex(next_vertex)
		{ }
};

const int max_vertices = ;
int num_vertices;
list<Edge> adj[max_vertices];		// adjacency list

vector<int> path;

void find_path(int v)
{
	while(adj[v].size() > 0)
	{
		int vn = adj[v].front().next_vertex;
		adj[vn].erase(adj[v].front().reverse_edge);
		adj[v].pop_front();
		find_path(vn);
	}
	path.push_back(v);
}

void add_edge(int a, int b)
{
	adj[a].push_front(Edge(b));
	iter ita = adj[a].begin();
	adj[b].push_front(Edge(a));
	iter itb = adj[b].begin();
	ita->reverse_edge = itb;
	itb->reverse_edge = ita;
}
