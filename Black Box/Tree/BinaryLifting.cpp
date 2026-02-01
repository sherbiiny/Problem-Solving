const int B = 21;
vector<vector<int>> adj;
vector<array<int, B>> up;
vector<int> lvl;

void dfs(int u, int p = 0, int d = 0) {
    lvl[u] = d;
    up[u][0] = p;
    for(int i = 1; i < B; ++i)
        up[u][i] = up[up[u][i - 1]][i - 1];

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