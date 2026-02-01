// Author: _Sherbiny

#include "bits/stdc++.h"
using namespace std;
using ll = long long;
#define endl '\n'
#define int ll
//====================//
const int oo = -2e18;

void magic() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int &i: a) cin >> i, --i;

    int lim = n * 2 + 2;
    vector vis(n, vector<int>(lim)), dp(n, vector(lim, oo));

    function<void(int, int)> move = [&](int u, int t) {
        if (t >= lim) return;
        vis[u][t] = 1;
        move(a[u], t + 1);
    };

    while (m--) {
        int x; cin >> x;
        move(--x, 0);
    }

    for (int u = 0; u < n; ++u) dp[u][lim - 1] = vis[u][lim - 1] * oo;
    for (int t = lim - 2; ~t; --t) {
        for (int u = 0; u < n; ++u) {
            if (vis[u][t]) continue;
            dp[u][t] = max(dp[u][t + 1] + 1, dp[a[u]][t + 1]);
        }
    }

    for (int u = 0; u < n; ++u) {
        int bad = count(vis[u].begin(), vis[u].end(), 1);
        if (!bad) {
            cout << -2 << endl;
            continue;
        }

        cout << max(dp[u][0], -1ll) << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t = 1;
    while (t--) magic();
}
