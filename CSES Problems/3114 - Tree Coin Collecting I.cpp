// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/3114

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

const int B = 21, oo = 2e18;
vector<vector<int>> adj;
vector<array<int, B>> up, bst;
vector<int> lvl, dist;

void dfs(int u, int p = 0, int d = 0) {
    lvl[u] = d;
    up[u][0] = p;
    bst[u][0] = dist[p];
    for(int i = 1; i < B; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        bst[u][i] = min(bst[u][i - 1], bst[up[u][i - 1]][i - 1]);
    }

    for(int &v: adj[u])
        if(v != p) dfs(v, u, d + 1);
}

int kthAncestor(int u, int k) {
    for(int i = B - 1; ~i; --i)
        if(k >> i & 1) u = up[u][i];
    return u;
}

int getLca(int u, int v) {
    if(lvl[u] > lvl[v]) swap(u, v);
    v = kthAncestor(v, lvl[v] - lvl[u]);

    for(int i = B - 1; ~i; --i)
        if(up[u][i] != up[v][i])
            u = up[u][i], v = up[v][i];

    return u == v? u : up[v][0];
}

int getDist(int u, int v) {
    return lvl[u] + lvl[v] - 2 * lvl[getLca(u, v)];
}

int query(int u, int v) {
    int ans = dist[v];

    for(int i = B - 1; ~i; --i) {
        if(lvl[up[v][i]] < lvl[u]) continue;
        ans = min(ans, bst[v][i]);
        v = up[v][i];
    }

    return ans;
}

int getMin(int u, int v) {
    int lca = getLca(u, v);
    return min(query(lca, u), query(lca, v));
}

void magic() {
    int n, m; cin >> n >> m;

    dist.assign(n + 1, oo);
    adj.assign(n + 1, {});
    up.assign(n + 1, {});
    bst.assign(n + 1, {});
    lvl.assign(n + 1, {});

    queue<int> q;
    bst[0].fill(oo);
    for(int i = 1; i <= n; ++i) {
        bst[i].fill(oo);
        int x; cin >> x;
        if(x) q.push(i), dist[i] = 0;
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    while(!q.empty()) {
        auto u = q.front();
        q.pop();
        for(int &v: adj[u])
            if(dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }

    dfs(1, 0);

    while (m--) {
        int u, v; cin >> u >> v;
        cout << getDist(u, v) + getMin(u, v) * 2 << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
