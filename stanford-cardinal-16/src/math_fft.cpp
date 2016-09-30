typedef complex<double> cd;
vector<cd> FFT(const vector<cd>& A, cd w) {
  if (A.size() == 1) return A;
  int M = (int) A.size(); // assumes M is a power of 2
  vector<cd> B[2] = { vector<cd>(M / 2), vector<cd>(M / 2) };
  for (int i = 0; i < M; ++i) B[i & 1][i >> 1] = A[i];
  cd ww = w * w;
  vector<cd> C[2] = { DFT(B[0], ww), DFT(B[1], ww) }, F(M);
  cd x = 1;
  for (int i = 0; i < M / 2; ++i) {
    F[i] = C[0][i] + x * C[1][i];
    F[i + M / 2] = C[0][i] - x * C[1][i];
    x = x * w;
  }
  return F;
}
