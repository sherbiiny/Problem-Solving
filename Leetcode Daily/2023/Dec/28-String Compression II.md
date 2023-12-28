```cpp
class Solution {
public:

    int cnt(int n) {
        if(n >= 100)
            return 4;
        else if(n > 9)
            return 3;
        else if(n > 1)
            return 2;
        else if(n > 0)
            return 1;
        return 0;
    }

    int getLengthOfOptimalCompression(string s, int k) {
        ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
        int n = s.size();

        int cost[n + 1][n + 1];
        for(int i = 0; i < n; ++i) {
            int need = 0;
            for(int j = i; j < n; ++j) {
                if(s[j] != s[i])
                    need++;
                cost[i][j + 1] = need;
            }
        }

        int dp[n + 1][k + 1];
        memset(dp[n], 0, sizeof dp[n]);

        for(int i = n - 1; i >= 0; --i) {
            for(int j = 0; j <= k; ++j) {
                dp[i][j] = 1 + dp[i+1][j];
                for(int go = i + 1; go <= n; ++go) {
                    int size = go - i - cost[i][go];
                    if(cost[i][go] <= j)
                        dp[i][j] = min(dp[i][j], cnt(size) + dp[go][j - cost[i][go]]);
                    if(go - i <= j)
                        dp[i][j] = min(dp[i][j], dp[go][j - go + i]);
                }
            }
        }

        return dp[0][k];
    }
};
```
