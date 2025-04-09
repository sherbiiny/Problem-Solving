// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1159

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

// you need to be able to take all possible amounts of each item
// you can do this by taking 1, 2, 4, 8, ... of each item
// and then take the remaining amount of the item
// this way you can cover all possible amounts of each item
// then simple knapsack will work

void magic() {
    int n, x; cin >> n >> x;
    vector<int> a(n), b(n), c(n);
    for(int &i: a) cin >> i;
    for(int &i: b) cin >> i;
    for(int &i: c) cin >> i;
    vector<array<int, 2>> v;

    for(int i = 0; i < n; ++i) {
        int take = 1;
        while(take <= c[i]) {
            v.push_back({take * b[i], take * a[i]});
            c[i] -= take;
            take *= 2;
        }

        v.push_back({c[i] * b[i], c[i] * a[i]});
    }

    n = v.size();
    int dp[2][x + 1];
    memset(dp, 0, sizeof dp);

    for(int i = n - 1; ~i; --i) {
        int it = i & 1;
        for(int j = 0; j <= x; ++j) {
            dp[it][j] = dp[it ^ 1][j];
            if(j >= v[i][1])
                dp[it][j] = max(dp[it][j], dp[it ^ 1][j - v[i][1]] + v[i][0]);
        }
    }

    cout << dp[0][x];
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
