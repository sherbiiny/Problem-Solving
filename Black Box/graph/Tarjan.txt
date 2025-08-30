// In case of multi edges, skip parent only one time
void dfs(int u, int p = -1) {
    in[u] = low[u] = timer++;

    int ch = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (in[v]) low[u] = min(low[u], in[v]);
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] > in[u]) IS_BRIDGE(u, v);
            if (low[v] >= in[u] && p!=-1) IS_ART(u);
            
            ++ch;
        }
    }

    if(p == -1 && ch > 1) IS_ART(v);
}