bool EulerPathUndir() {
    int st = -1, en = -1, cand = 1;
    for(int u = 1; u <= n; ++u) {
        if(!adj[u].empty()) cand = u;
        if(deg[u] & 1) {
            if(st == -1) st = u;
            else if(en == -1) en = u;
            else return false;
        }
    }

    if(st == -1) st = cand;
    else if(en == -1) return false;

    vector<int> edges, nodes, vis(m);
    auto dfs = [&](auto &&dfs, int u) -> void {
        while(!adj[u].empty()) {
            auto [v, i] = adj[u].back();
            adj[u].pop_back();
            if(vis[i]) continue;
            vis[i] = 1, dfs(dfs, v);
            edges.push_back(i);
            nodes.push_back(v);
        }
    };

    dfs(dfs, st);
    if(size(edges) != m) return false;
    nodes.push_back(st);
    reverse(nodes.begin(), nodes.end());
    reverse(edges.begin(), edges.end());
    return true;
}