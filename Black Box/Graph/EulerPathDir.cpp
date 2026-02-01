// deg[u] = out[u] - in[u]
bool EulerPathDir() {
    int st = -1, en = -1, cand = 1;
    for(int u = 1; u <= n; ++u) {
        if(abs(deg[u]) > 1) return false;
        if(!adj[u].empty()) cand = u;

        if(deg[u] == 1) {
            if(~st) return false;
            st = u;
        }

        if(deg[u] == -1) {
            if(~en) return false;
            en = u;
        }
    }

    if(st == -1) st = cand;
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