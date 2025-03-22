// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/2432
 
#include "bits/stdc++.h"
using namespace std;
 
typedef long long ll;
#define endl '\n'
#define int ll
//==================//
 
static const int oo = 2e18;
 
struct Edge {
    int u, v, flow = 0, cap = 0; // keep the order
 
    Edge(int u, int v): u(u), v(v) {}
    Edge(int u, int v, int c): u(u), v(v), cap(c) {}
 
    int rem() { return cap - flow; }
};
 
struct Dinic {
    int n, s, t, id = 1;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> lvl, ptr, curr;
 
    Dinic(int n, int src, int sink): n(n), s(src), t(sink) {
        adj.assign(n + 1, {});
        ptr.assign(n + 1, {});
        curr.push_back(s);
    }
 
    void addEdge(int u, int v, int w = oo, int undir = 0) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(u, v, w));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(v, u, w * undir));
    }
 
    int flow() {
        int res = 0;
        while(bfs()) {
            ptr.assign(n + 1, {});
            while (int flow = dfs(s)) res += flow;
        }
        return res;
    }
 
    bool bfs() {
        lvl.assign(n + 1, -1);
        queue<int> q;
        q.push(s), lvl[s] = 0;
 
        while(!q.empty()) {
            auto u = q.front();
            q.pop();
 
            for(auto &i: adj[u]) {
                auto &[_, v, f, c] = edges[i];
                if(~lvl[v] || f == c) continue;
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }
 
        return lvl[t] != -1;
    }
 
    int dfs(int u, int flow = oo) {
        if(!flow) return 0;
        if(u == t) return flow;
 
        for(; ptr[u] < adj[u].size(); ++ptr[u]) {
            int i = adj[u][ptr[u]];
            auto [_, v, f, c] = edges[i];
            if(f == c || lvl[v] != lvl[u] + 1) continue;
 
            int bottleNeck = dfs(v, min(flow, c - f));
            if(!bottleNeck) continue;
 
            edges[i].flow += bottleNeck;
            edges[i ^ 1].flow -= bottleNeck;
 
            return bottleNeck;
        }
 
        return 0;
    }
 
    // get any set of edges to achieve the min cut (max flow)
    vector<array<int, 2>> getEdges() {
        vector<int> srcSide(n + 1);
        queue<int> q;
        q.push(s), srcSide[s] = 1;
 
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto &i: adj[u]) {
                auto &[_, v, f, c] = edges[i];
                if(!srcSide[v] && f != c) q.push(v), srcSide[v] = 1;
            }
        }
 
        vector<array<int, 2>> res;
        for(int i = 0; i < edges.size(); i += 2) {
            auto &[u, v, f, c] = edges[i];
            if(srcSide[u] && !srcSide[v]) res.push_back({u, v});
        }
 
        return res;
    }
};
 
void magic() {
    int n; cin >> n;
    int s = n * 2, t = s + 1;
    Dinic g(n * 2 + 1, s, t);
 
    vector<int> a(n), b(n);
    int sa = 0, sb = 0;
    for(auto &i: a) cin >> i, sa += i;
    for(auto &i: b) cin >> i, sb += i;
 
    if(sa != sb)
        return void(cout << -1);
 
    for(int i = 0; i < n; ++i) {
        g.addEdge(s, i, a[i]);
        g.addEdge(i + n, t, b[i]);
        for(int j = 0; j < n; ++j) g.addEdge(i, j + n, 1);
    }
 
    if(g.flow() != sa)
        return void(cout << -1);
 
    vector res(n, vector(n, '.'));
 
    for(auto &[u, v, f, c]: g.edges) {
        if(!c || u == s || v == t) continue;
        if(f) res[u][v - n] = 'X';
    }
 
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j)
            cout << res[i][j];
        cout << endl;
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) magic();
}