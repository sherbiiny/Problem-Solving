struct LCA {
    static const int B = 21;
    vector<array<int, 2>> tour;
    vector<array<array<int, 2>, B>> T;
    vector<int> d, in, lg;

    LCA(int n, auto &adj): d(n + 1), in(n + 1), lg(n*2 + 1) {
        tour.reserve(n *= 2);
        T.resize(n);
        dfs(0, 0, adj);
        for(int i = 0; i < n; ++i) lg[i]=__lg(i), T[i][0]=tour[i];
        for (int j = 1; j < B; ++j)
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
                T[i][j] = min(T[i][j - 1], T[i+(1 << j - 1)][j - 1]);
    }

    void dfs(int u, int p, auto &adj) {
        in[u] = size(tour);
        tour.push_back({d[u], u});
        for (int v: adj[u]) {
            if (v == p) continue;
            d[v] = d[u] + 1;
            dfs(v, u, adj);
            tour.push_back({d[u], u});
        }
    }

    int get(int u, int v) {
        int l = min(in[u], in[v]), r = max(in[u], in[v]);
        int j = lg[r - l + 1];
        return min(T[l][j], T[r - (1 << j) + 1][j])[1];
    }

    int dist(int u, int v) { return d[u]+d[v]-2*d[get(u, v)]; }
};