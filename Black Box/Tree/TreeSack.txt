void getSz(int u, int p = 0) {
    sz[u] = 1;
    for(auto v: adj[u])
        if(v != p) getSz(v, u), sz[u] += sz[v];
}

void upd(int u, int t) {}

void add(int u, int t, int p) {
    upd(u, t);
    for(auto v: adj[u])
        if(v != p) add(v, t, u);
}

void go(int u, int p = 0, int keep = 0) {
    array<int, 2> bg{-1, -1};
    for(auto v: adj[u])
        if(v != p) bg = max(bg, {sz[v], v});

    for(auto v: adj[u]) {
        if(v == p || v == bg[1]) continue;
        go(v, u);
    }

    if(~bg[1]) go(bg[1], u, 1);

    upd(u, 1);
    for(auto v: adj[u])
        if(v != bg[1] && v != p) add(v, 1, u);

    if(!keep) add(u, 0, p);
}