```cpp
int numRollsToTarget(int n, int k, int target) {
    int dp[2][target + 1];
    memset(dp[n&1], 0, sizeof dp[n&1]);
    dp[n & 1][0] = 1;
    const int mod = 1000000007;
    for (int i = n - 1; i >= 0; --i) {
        bool it = i & 1;
        dp[it][0] = 0;
        for (int j = 1; j <= target; ++j) {
            dp[it ^ 1][j] += dp[it ^ 1][j - 1];
            if (dp[it ^ 1][j] >= mod)
                dp[it ^ 1][j] -= mod;

            dp[it][j] = dp[it ^ 1][j - 1];
            if (j - k - 1 >= 0)
                dp[it][j] -= dp[it ^ 1][j - k - 1];

            if (dp[it][j] < 0)
                dp[it][j] += mod;
        }
    }

    return dp[0][target];
}
```
