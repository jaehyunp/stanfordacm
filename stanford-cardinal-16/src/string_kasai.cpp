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
