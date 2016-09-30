#include <bits/stdc++.h>
#define FOR(i, n) for (int i = 0; i < (n); ++i)
#define REP(i, n) for (int i = 1; i <= (n); ++i)
using namespace std;

struct KMP {
  int N;
  const string S;
  vector<int> F;
  KMP(const string S): S(S) {
    N = S.size();
    F.assign(N + 1, 0);
    for (int i = 1; i < N; ++i)
      F[i + 1] = advance(F[i], S[i]);
  }
  void match(const string T) {
    for (int i = 0, j = 0; i < (int) T.size(); ++i) {
      j = advance(j, T[i]);
      if (j == N)
        cout << "match ends at " << i << endl;
    }
  }
  int advance(int j, char x) {
    while (j && (j == N || S[j] != x)) j = F[j];
    if (S[j] == x) ++j;
    return j;
  }
  int minfactor() {
    int factor = N;
    for (int i = F[N]; i; i = F[i])
      if (N % (N - i) == 0) {
        factor = N - i;
        break;
      }
    return factor;
  }
};

char S[1 << 20], T[1 << 20];

int main() {
  cin >> S;
  KMP matcher(S);
  cin >> T;
  matcher.match(T);
  cout << matcher.minfactor() << endl;
  return 0;
}
