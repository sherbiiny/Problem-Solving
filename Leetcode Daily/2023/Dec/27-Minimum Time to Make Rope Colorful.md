```cpp
int minCost(string colors, vector<int>& neededTime) {
    int dp[2][27];
    for(int i = 0; i < 27; ++i)
        dp[colors.size()&1][i] = 0;

    for(int i = colors.size() - 1; i >= 0; --i) {
        for(int j = 0; j < 27; ++j) {
            dp[i & 1][j] = neededTime[i] + dp[!(i & 1)][j];
            if(j != colors[i] - 'a')
                dp[i&1][j] = min(dp[i&1][j], dp[!(i & 1)][colors[i] - 'a']);
        }
    }

    return dp[0][26];
}
```
