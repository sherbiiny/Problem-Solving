const int oo = 2e18;
vector<array<int, 3>> edg;

// to find any negative cycle set all d = 0
vector<int> bellman(int n, int s) {
    vector d(n + 1, oo), p(n + 1, 0ll);
    d[s] = 0;

    int lst = -1;
    for(int i = 0; i <= n; ++i) {
        lst = -1;
        for(auto &[u, v, w]: edg)
            if(d[u] + w < d[v])
                d[v] = d[u] + w, lst = v, p[v] = u;
        if(lst == -1) break;
    }

    // no negative cycle
    if (lst == -1) return d;

    for(int i = 0; i < n; ++i)
        for(auto &[u, v, w]: edg)
            if(d[u] < oo && d[u] + w < d[v]) d[v] = -oo;

    int y = lst;
    for (int i = 0; i < n; ++i) y = p[y];

    vector<int> cyc;
    for (int v = y;; v = p[v]) {
        cyc.push_back(v);
        if (v == y && cyc.size() > 1) break;
    }
    reverse(cyc.begin(), cyc.end());

    return d;
}