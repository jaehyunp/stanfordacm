int partition(int n) {
  int[] dp = new int[n + 1];
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1, r = 1; i - (3 * j * j - j) / 2 >= 0; j++, r *= -1) {
      dp[i] += dp[i - (3 * j * j - j) / 2] * r;
      if (i - (3 * j * j + j) / 2 >= 0) {
        dp[i] += dp[i - (3 * j * j + j) / 2] * r;
      }
    }
  }
  return dp[n];
}
