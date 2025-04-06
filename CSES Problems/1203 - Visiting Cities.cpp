// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1203

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<long long>(l, r)(rng)

const int oo = 2e18;
template<class T>
using minPQ = priority_queue<T, vector<T>, greater<>>;


void magic() {
    int n, m; cin >> n >> m;
    array<vector<vector<array<int, 2>>>, 2> adj;
    adj[0].assign(n + 1, {});
    adj[1].assign(n + 1, {});

    for(int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[0][u].push_back({v, w});
        adj[1][v].push_back({u, w});
    }

    auto check = [](int x) {
        for (int i = 2; i * i <= x; ++i)
            if (!(x % i)) return false;
        return true;
    };

    int mod = getrand(1e8, 1e9);
    while(!check(mod)) --mod;

    auto dijkstra = [&](int src, int t) -> array<vector<int>, 2> {
        vector<int> dist(n + 1, oo), cnt(n + 1, 0);
        minPQ<pair<int, int>> pq;
        dist[src] = 0, cnt[src] = 1;
        pq.emplace(0, src);

        while(!pq.empty()) {
            auto [cost, u] = pq.top();
            pq.pop();

            if(dist[u] < cost) continue;

            for(auto [v, w] : adj[t][u]) {
                if(dist[u] + w >= dist[v]) {
                    cnt[v] += (dist[u] + w == dist[v]) * cnt[u];
                    cnt[v] %= mod;
                    continue;
                }

                cnt[v] = cnt[u];
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }

        return {dist, cnt};
    };

    auto [a, b] = dijkstra(1, 0);
    auto [x, y] = dijkstra(n, 1);

    vector<int> res;
    for(int u = 1; u <= n; ++u) {
        if(a[u] + x[u] != a[n]) continue;
        if(b[u] * y[u] % mod == b[n]) res.push_back(u);
    }

    cout << res.size() << endl;
    for(auto &u: res) cout << u << ' ';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
