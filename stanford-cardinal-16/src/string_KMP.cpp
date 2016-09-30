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
  int advance(int j, char x) {
    while (j && (j >= N || S[j] != x)) j = F[j];
    if (S[j] == x) ++j;
    return j;
  }
  void match(const string T) {
    int j = 0;
    for (auto c : T) {
      j = advance(j, c);
      if (j == N) cout << "match" << endl;
    }
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
