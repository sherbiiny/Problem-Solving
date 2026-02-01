struct DSU {
    int n, cnt;
    vector<int> p, sz;

    DSU(int n): n(n), cnt(n), p(n + 1), sz(n + 1, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int u) {
        if(u == p[u]) return u;
        return p[u] = find(p[u]);
    }

    bool same(int u, int v) { return find(u) == find(v); }

    bool merge(int u, int v) {
        int uP = find(u), vP = find(v);
        if(vP == uP) return false;

        if(sz[vP] > sz[uP]) swap(uP, vP);
        sz[uP] += sz[vP], p[vP] = uP, cnt--;

        return true;
    }
};