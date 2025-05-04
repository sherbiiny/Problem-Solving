// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1757

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

void magic() {
    int n, m; cin >> n >> m;

    vector<int> in(n + 1);
    vector<vector<int>> adj(n + 1);
    while(m--) {
        int u, v; cin >> u >> v;
        adj[v].push_back(u);
        in[u]++;
    }

    priority_queue<int> pq;
    vector<int> res;
    for(int u = 1; u <= n; ++u)
        if(!in[u]) pq.push(u);

    while(!pq.empty()) {
        int u = pq.top();
        pq.pop();

        res.push_back(u);
        for(int &v: adj[u]) {
            --in[v];
            if(!in[v]) pq.push(v);
        }
    }

    reverse(res.begin(), res.end());

    for(int &u: res) cout << u << ' ';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
