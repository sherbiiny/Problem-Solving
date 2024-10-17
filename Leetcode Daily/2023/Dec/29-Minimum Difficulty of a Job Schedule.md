```cpp
typedef long long ll;

class Solution {
public:
    int minDifficulty(vector<int> job, int d) {
        int n = job.size();
        if(n < d)
            return -1;

        // dp[i][mx][d] the min val to finish jobs from i having mx job and d remaining day
        ll dp[2][n + 1][d];
        for(int i = 0; i < n; ++i){
            dp[n&1][i][0] = job[i];
            for(int k = 1; k < d; ++k)
                dp[n&1][i][k] = 2e9;
        }

        for(int i = n - 1; i >= 0; --i) {
            bool it = i&1;
            for(int k = 0; k < d; ++k) {
                for(int j = 0; j <= i; ++j) {
                    if(job[i] > job[j])
                        dp[it][j][k] = dp[!it][i][k];
                    else
                        dp[it][j][k] = dp[!it][j][k];

                    int cost = max(job[j], job[i]);

                    if(k && i < n - 1)
                        dp[it][j][k] = min(dp[it][j][k], cost + dp[!it][i + 1][k - 1]);
                }
            }
        }

        return dp[0][0][d - 1];
    }
};
```
