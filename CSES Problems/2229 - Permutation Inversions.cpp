// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/2229

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
//====================//
 
void magic() {
    int n, k; cin >> n >> k;
 
    int dp[2][k + 1];
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
 
    // dp[i][j] = number of ways to make j inversions using first i elements
    // dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] + dp[i - 1][j - 2] + ... + dp[i - 1][j - i + 1]
    // the idea of the trastion is to see if you add the i-th element to the permutation
    // then you can create number of inversions from 0 to i - 1
    // this transition can be done in O(1) using prefix sums

    const int mod = 1e9 + 7;
    for(int i = 1; i <= n; ++i) {
        int it = i & 1;
 
        vector<int> pref(k + 1);
        for(int j = 0; j <= k; ++j) {
            pref[j] = dp[it ^ 1][j];
            if(j) pref[j] += pref[j - 1];
            if(pref[j] >= mod) pref[j] -= mod;
        }
 
        for(int j = 0; j <= k; ++j) {
            int l = j - min(i - 1, j);
            dp[it][j] = pref[j] - (l? pref[l - 1] : 0);
            
            if(dp[it][j] >= mod) dp[it][j] -= mod;
            if(dp[it][j] < 0) dp[it][j] += mod;
        }
    }
 
    cout << dp[n & 1][k];
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}