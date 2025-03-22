// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1664

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//
 
static const int B = 21;
const int oo = 2e18;
 
// Binary Lifting

void magic() {
    int n, q; cin >> n >> q;
    vector<array<int, 2>> v(n);
    for(auto &[l, r]: v) cin >> l >> r;
    sort(v.begin(), v.end());
 
    vector<array<array<int, 2>, B>> dp(n + 1);
    dp[n].fill({oo, n});
 
    for(int i = n - 1; i >= 0; --i) {
        array srch{v[i][1], -oo};
        int to = lower_bound(v.begin(), v.end(), srch) - v.begin();
 
        array me{v[i][1], to};
        dp[i][0] = min(me, dp[i + 1][0]);
 
        for(int j = 1; j < B; ++j)
            dp[i][j] = dp[dp[i][j - 1][1]][j - 1];
    }
 
    while(q--) {
        int l, r; cin >> l >> r;
        array srch{l, -oo};
        int u = lower_bound(v.begin(), v.end(), srch) - v.begin();
 
        int ans = 0;
        for(int i = B - 1; i >= 0; --i)
            if(dp[u][i][0] <= r) {
                u = dp[u][i][1];
                ans += 1ll << i;
            }
 
        cout << ans << endl;
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}