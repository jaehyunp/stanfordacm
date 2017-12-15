#include<bits/stdc++.h>
using namespace std;
///////////////////// UNION FIND ////////////////////////
typedef struct _dsu{
  //USAGE: DSU <name>(<size>); <name>.merge(x,y); <name>.find(x);
  vector<int> par;
  _dsu(int n)       {par.resize(n); for(int i=0;i<n;++i) par[i]=i;}
  int find(int x)   {return x==par[x]?x:par[x]=find(par[x]);}
  void merge(int x, int y)  {par[find(x)]=par(y);}
} DSU;

int main()
{
	int n = 5; DSU dsu(n);
	dsu.merge(0, 2);
	dsu.merge(1, 0);
	dsu.merge(3, 4);
	for (int i = 0; i < n; i++) cout << i << " " << dsu.find(i) << endl;
	return 0;
}
