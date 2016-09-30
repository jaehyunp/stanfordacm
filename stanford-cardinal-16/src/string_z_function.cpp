void compute_z_function(const char *S, int N) {
  // Z[i] is the length of longest substring
  // starting from S[i] which matches a prefix of S.
  int L = 0, R = 0;
  for (int i = 1; i < N; ++i) {
    if (i > R) {
      L = R = i;
      while (R < N && S[R - L] == S[R]) ++R;
      Z[i] = R - L; --R;
    } else {
      int k = i - L;
      if (Z[k] < R - i + 1) Z[i] = Z[k];
      else {
        L = i;
        while (R < N && S[R - k] == S[R]) ++R;
        Z[i] = R - L; --R;
      }
    }
  }
}
