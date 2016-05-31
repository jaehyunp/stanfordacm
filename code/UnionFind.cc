#include <iostream>
#include <vector>
using namespace std;
int find(vector<int> &C, int x) { return (C[x] == x) ? x : C[x] = find(C, C[x]); }
void merge(vector<int> &C, int x, int y) { C[find(C, x)] = find(C, y); }
int main()
{
	int n = 5;
	vector<int> C(n);
	for (int i = 0; i < n; i++) C[i] = i;
	merge(C, 0, 2);
	merge(C, 1, 0);
	merge(C, 3, 4);
	for (int i = 0; i < n; i++) cout << i << " " << find(C, i) << endl;
	return 0;
}
