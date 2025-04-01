// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1706

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
//====================//

vector<vector<int>> adj;
vector<int> vis;

const int N = 1e5 + 10;
bitset<N> dp;

int dfs(int u) {
    vis[u] = 1;
    int c = 1;
    for(int &v: adj[u])
        if(!vis[v]) c += dfs(v);
    return c;
}

void magic() {
    int n, m; cin >> n >> m;
    adj.assign(n + 1, {});
    vis.assign(n + 1, {});

    for(int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dp[0] = 1;
    for(int u = 1; u <= n; ++u) {
        if(vis[u]) continue;
        dp |= dp << dfs(u);
    }

    for(int i = 1; i <= n; ++i)
        cout << dp[i];
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
