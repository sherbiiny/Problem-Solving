// for a root r
// dom[u] is the lowest node that exists on all paths from r to u
struct DominatorTree {
    int T = 0, n;
    vector<vector<int>> rg, bucket, adj;
    vector<int> dsu, par, sdom, idom, dom, label, id, rev;

    DominatorTree(int n, int r, auto& adj):
        n(n++), rg(n), bucket(n), adj(adj), dsu(n),
        par(n), sdom(n), idom(n), dom(n), label(n), id(n), rev(n) { dfs(r), build(); }

    int find(int u, int x = 0) {
        if (u == dsu[u]) return x ? -1 : u;
        int v = find(dsu[u], x + 1);
        if (v < 0) return u;
        if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
        dsu[u] = v;
        return x ? v : label[u];
    }

    void dfs(int u) {
        id[u] = ++T, rev[T] = u;
        label[T] = sdom[T] = dsu[T] = T;
        for (int& w : adj[u]) {
            if (!id[w]) dfs(w), par[id[w]] = id[u];
            rg[id[w]].push_back(id[u]);
        }
    }

    void build() {
        for (int i = n; i; i--) {
            for (int& u : rg[i]) sdom[i] = min(sdom[i], sdom[find(u)]);
            if (i > 1) bucket[sdom[i]].push_back(i);
            for (int& w : bucket[i]) {
                int v = find(w);
                idom[w] = sdom[v] == sdom[w] ? sdom[w] : v;
            }
            if (i > 1) dsu[i] = par[i];
        }

        for (int i = 2; i <= n; i++)
            if (idom[i] != sdom[i]) idom[i] = idom[idom[i]];

        for (int u = 1; u <= n; ++u) dom[rev[u]] = rev[idom[u]];
    }
};