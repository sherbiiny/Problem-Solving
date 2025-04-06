// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1677

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
//====================//

struct DSU {
    int n, cnt;
    vector<int> p, sz;

    DSU(int n): n(n), cnt(n), p(n + 1), sz(n + 1, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int u) {
        if(u == p[u]) return u;
        return p[u] = find(p[u]);
    }

    bool same(int u, int v) { return find(u) == find(v); }

    bool merge(int u, int v) {
        int uP = find(u), vP = find(v);
        if(vP == uP) return false;

        if(sz[vP] > sz[uP]) swap(uP, vP);
        sz[uP] += sz[vP], p[vP] = uP, cnt--;

        return true;
    }
};

void magic() {
    int n, m, k; cin >> n >> m >> k;
    vector<array<int, 3>> edg(m);

    map<array<int, 2>, int> id;
    for(auto &[t, u, v]: edg) {
        cin >> u >> v;
        if(u > v) swap(u, v);
        id[{u, v}] = id.size();
    }

    while(k--) {
        int u, v; cin >> u >> v;
        if(u > v) swap(u, v);
        edg[id[{u, v}]][0] = k + 1;
    }

    sort(edg.begin(), edg.end());
    vector<int> res;

    DSU dsu(n);
    for(auto &[t, u, v]: edg) {
        if(t) res.push_back(dsu.cnt);
        dsu.merge(u, v);
    }

    reverse(res.begin(), res.end());
    for(auto &x: res) cout << x << ' ';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
