// O(n ^ 2)
auto shortestCycle = [&] {
    int ans = oo;
    for (int s = 1; s <= n; ++s) {
        queue<int> q;
        vector<int> p(n + 1, -1), d(n + 1, -1);
        d[s] = 0, q.push(s);

        while(!q.empty()) {
            int u = q.front(); q.pop();
            for (int &v: adj[u]) {
                if (d[v] == -1) {
                    d[v] = 1 + d[u], p[v] = u;
                    q.push(v);
                } else if (p[u] != v) {
                    ans = min(ans, d[v] + d[u] + 1);
                }
            }
        }
    }

    return ans;
};