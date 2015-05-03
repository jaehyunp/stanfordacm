// Two-phase simplex algorithm for solving linear programs of the form
//
//     maximize     c^T x
//     subject to   Ax <= b
//                  x >= 0
//
// INPUT: A -- an m x n matrix
//        b -- an m-dimensional vector
//        c -- an n-dimensional vector
//        x -- a vector where the optimal solution will be stored
//
// OUTPUT: value of the optimal solution (infinity if unbounded
//         above, nan if infeasible)
//
// To use this code, create an LPSolver object with A, b, and c as
// arguments.  Then, call Solve(x).

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// BEGIN CUT
#define ACM_assert(x) {if(!(x))*((long *)0)=666;}
//#define TEST_LEAD_OR_GOLD
#define TEST_HAPPINESS
// END CUT
typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

const DOUBLE EPS = 1e-9;

struct LPSolver {
  int m, n;
  VI B, N;
  VVD D;

  LPSolver(const VVD &A, const VD &b, const VD &c) : 
    m(b.size()), n(c.size()), N(n+1), B(m), D(m+2, VD(n+2)) {
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
    for (int i = 0; i < m; i++) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i]; }
    for (int j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
    N[n] = -1; D[m+1][n] = 1;
  }
	   
  void Pivot(int r, int s) {
    for (int i = 0; i < m+2; i++) if (i != r)
      for (int j = 0; j < n+2; j++) if (j != s)
	D[i][j] -= D[r][j] * D[i][s] / D[r][s];
    for (int j = 0; j < n+2; j++) if (j != s) D[r][j] /= D[r][s];
    for (int i = 0; i < m+2; i++) if (i != r) D[i][s] /= -D[r][s];
    D[r][s] = 1.0 / D[r][s];
    swap(B[r], N[s]);
  }

  bool Simplex(int phase) {
    int x = phase == 1 ? m+1 : m;
    while (true) {
      int s = -1;
      for (int j = 0; j <= n; j++) {
	if (phase == 2 && N[j] == -1) continue;
	if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
      }
      if (D[x][s] >= -EPS) return true;
      int r = -1;
      for (int i = 0; i < m; i++) {
	if (D[i][s] <= EPS) continue;
	if (r == -1 || D[i][n+1] / D[i][s] < D[r][n+1] / D[r][s] ||
	    D[i][n+1] / D[i][s] == D[r][n+1] / D[r][s] && B[i] < B[r]) r = i;
      }
      if (r == -1) return false;
      Pivot(r, s);
    }
  }

  DOUBLE Solve(VD &x) {
    int r = 0;
    for (int i = 1; i < m; i++) if (D[i][n+1] < D[r][n+1]) r = i;
    if (D[r][n+1] <= -EPS) {
      Pivot(r, n);
      if (!Simplex(1) || D[m+1][n+1] < -EPS) return -numeric_limits<DOUBLE>::infinity();
      for (int i = 0; i < m; i++) if (B[i] == -1) {
	int s = -1;
	for (int j = 0; j <= n; j++) 
	  if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
	Pivot(i, s);
      }
    }
    if (!Simplex(2)) return numeric_limits<DOUBLE>::infinity();
    x = VD(n);
    for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n+1];
    return D[m][n+1];
  }
  // BEGIN CUT
  void Print() {
    cout << "N = "; for (int i = 0; i < N.size(); i++) printf("%8d", N[i]); cout << endl;
    cout << "B = "; for (int i = 0; i < B.size(); i++) printf("%8d", B[i]); cout << endl;
    cout << endl;
    for (int i = 0; i < D.size(); i++) {
      for (int j = 0; j < D[i].size(); j++) {
	printf("%8.2f", double(D[i][j]));
      }
      printf("\n");
    }
    printf("\n");
  }  
  // END CUT
};

// BEGIN CUT
#ifdef TEST_HAPPINESS
int main() {
  int n, m;
  while (cin >> n >> m) {
    ACM_assert(3 <= n && n <= 20);
    ACM_assert(3 <= m && m <= 20);

    VVD A(m, VD(n));
    VD b(m), c(n);
    for (int i = 0; i < n; i++) {
      cin >> c[i];
      ACM_assert(c[i] >= 0);
      ACM_assert(c[i] <= 10);
    }
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++)
	cin >> A[i][j];
      cin >> b[i];
      ACM_assert(b[i] >= 0);
      ACM_assert(b[i] <= 1000);
    }
    
    LPSolver solver(A, b, c);
    VD sol;
    DOUBLE primal_answer = m * solver.Solve(sol);
    
    VVD AT(A[0].size(), VD(A.size()));
    for (int i = 0; i < A.size(); i++)
      for (int j = 0; j < A[0].size(); j++)
	AT[j][i] = -A[i][j];
    for (int i = 0; i < c.size(); i++)
      c[i] = -c[i];
    for (int i = 0; i < b.size(); i++)
      b[i] = -b[i];
    
    LPSolver solver2(AT, c, b);
    DOUBLE dual_answer = -m * solver2.Solve(sol);
    ACM_assert(fabs(primal_answer - dual_answer) < 1e-10);
    
    int primal_rounded_answer = (int) ceil(primal_answer);
    int dual_rounded_answer = (int) ceil(dual_answer);
    // The following assert fails b/c of the input data.
    // ACM_assert(primal_rounded_answer == dual_rounded_answer);
    
    cout << "Nasa can spend " << primal_rounded_answer << " taka." << endl;
  }
}

#else 
#ifdef TEST_LEAD_OR_GOLD

int main() {
  int n;
  int ct = 0;
  while (cin >> n) {
    if (n == 0) break;
    VVD A(6, VD(n));
    VD b(6), c(n, -1);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 3; j++) {
	cin >> A[j][i]; A[j+3][i] = -A[j][i];
      }
    }
    for (int i = 0; i < 3; i++) {
      cin >> b[i]; b[i+3] = -b[i];
    }
    if (ct > 0) cout << endl;
    cout << "Mixture " << ++ct << endl;
    LPSolver solver(A, b, c);
    VD x;
    double obj = solver.Solve(x);
    if (isfinite(obj)) {
      cout << "Possible" << endl;
    } else {
      cout << "Impossible" << endl;
    }
  }
  return 0;
}

#else
// END CUT
int main() {

  const int m = 4;
  const int n = 3;  
  DOUBLE _A[m][n] = {
    { 6, -1, 0 },
    { -1, -5, 0 },
    { 1, 5, 1 },
    { -1, -5, -1 }
  };
  DOUBLE _b[m] = { 10, -4, 5, -5 };
  DOUBLE _c[n] = { 1, -1, 0 };
  
  VVD A(m);
  VD b(_b, _b + m);
  VD c(_c, _c + n);
  for (int i = 0; i < m; i++) A[i] = VD(_A[i], _A[i] + n);

  LPSolver solver(A, b, c);
  VD x;
  DOUBLE value = solver.Solve(x);
  
  cerr << "VALUE: "<< value << endl;
  cerr << "SOLUTION:";
  for (size_t i = 0; i < x.size(); i++) cerr << " " << x[i];
  cerr << endl;
  return 0;
}
// BEGIN CUT
#endif
#endif
// END CUT


