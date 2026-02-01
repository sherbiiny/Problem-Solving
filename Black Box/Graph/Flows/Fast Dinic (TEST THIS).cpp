static const int oo = 2e15;

struct Edge {
    int u, v, flow = 0, cap = 0; // keep the order
    Edge(int u, int v): u(u), v(v) {}
    Edge(int u, int v, int c): u(u), v(v), cap(c) {}
    int rem() { return cap - flow; }
};

struct Dinic {
    int n, s, t, flow = 0;
    vector<int> lvl, ptr, q;
    vector<vector<int>> adj;
    vector<Edge> edges;

    Dinic(int n, int s, int t):
        n(++n), s(s), t(t), lvl(n), ptr(n), q(n), adj(n) {}

    void addEdge(int u, int v, int w = oo, int undir = 0) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(u, v, w));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(v, u, w * undir));
    }

    int dfs(int u, int cf = oo) {
        if(u == t || !cf) return cf;

        for(; ptr[u] < adj[u].size(); ++ptr[u]) {
            int i = adj[u][ptr[u]];
            auto &[_, v, f, c] = edges[i];
            if(f == c || lvl[v] != lvl[u] + 1) continue;

            int p = dfs(v, min(cf, c - f));
            if(!p) continue;

            edges[i].flow += p;
            edges[i ^ 1].flow -= p;

            return p;
        }

        return 0;
    }

    void move() {
        q[0] = s;
        for (int L = 0; L <= 30; L++) do {
            lvl = ptr = vector<int>(n);
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                int u = q[qi++];
                for (int &i: adj[u]) {
                    auto &[_, v, f, c] = edges[i];
                    if (!lvl[v] && (c - f) >> (30 - L))
                        q[qe++] = v, lvl[v] = lvl[u] + 1;
                }
            }
            while (int f = dfs(s, oo)) flow += f;
        } while (lvl[t]);
    }
};