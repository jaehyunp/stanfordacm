#include <bits/stdc++.h>
#define FOR(i, n) for (int i = 0; i < (n); ++i)
#define ROF(i, n) for (int i = (n) - 1; i >= 0; --i)
#define REP(i, n) for (int i = 1; i <= (n); ++i)
using namespace std;

const int MAXN = 1000001;
char S[MAXN];

int N, SA[MAXN], *RA, *RA2, RA_tmp[2][MAXN], k;

bool cmp(const int& i, const int& j) {
  if (RA[i] != RA[j]) return RA[i] < RA[j];
  return (i + k < N && j + k < N) ? RA[i + k] < RA[j + k] : i > j;
}

void suffix_array() {
  RA = RA_tmp[0]; RA2 = RA_tmp[1];
  iota(SA, SA + N, 0);
  FOR (i, N) RA[i] = S[i];
  for (k = 1; k < N; k <<= 1) {
    sort(SA, SA + N, cmp);
    RA2[SA[0]] = 0;
    for (int i = 1; i < N; ++i) RA2[SA[i]] = RA2[SA[i - 1]] + cmp(SA[i - 1], SA[i]);
    swap(RA, RA2);
    if (RA[SA[N - 1]] == N - 1) break;
  }
}

int invSA[MAXN], PLCP[MAXN];
void kasai() {
  int l = 0;
  for (int i = 0; i < N; ++i) invSA[SA[i]] = i;
  for (int i = 0; i < N; ++i) {
    if (l > 0) --l;
    if (invSA[i] != 0)
        while (i + l < N && SA[invSA[i] - 1] + l < N &&
               S[i + l] == S[SA[invSA[i] - 1] + l]) ++l;
    PLCP[invSA[i]] = l;
    // PLCP[j] = LCP of suffix SA[j] and SA[j - 1]
  }
}

int main() {
  scanf("%s", S);
  N = strlen(S);
  suffix_array();

  kasai();
  FOR (i, N) printf("%d %d\n", SA[i], PLCP[i]);
  return 0;
}
