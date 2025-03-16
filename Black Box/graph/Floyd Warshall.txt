vector<vector<int>> d(n + 1, vector<int>(n + 1, oo));
for(int u = 1; u <= n; ++u)
    d[u][u] = 0;

for(int i = 0; i < m; ++i) {
    int u, v, c; cin >> u >> v >> c;
    d[u][v] = min(d[u][v], c);
    d[v][u] = min(d[v][u], c);
}

for(int k = 1; k <= n; ++k)
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);