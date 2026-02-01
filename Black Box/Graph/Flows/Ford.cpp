// O(E * MaxFlow)

static const int oo = 2e15;

struct Edge {
    int u, v, flow = 0, cap = 0; // keep the order

    Edge(int u, int v): u(u), v(v) {}
    Edge(int u, int v, int c): u(u), v(v), cap(c) {}

    int rem() { return cap - flow; }
};

struct Ford {
    int n, s, t, id = 1;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> vis;

    Ford(int n, int s, int t): n(n), s(s), t(t) {
        adj.assign(n + 1, {});
        vis.assign(n + 1, {});
    }

    // undir = 1 --> the edge is undirected
    void addEdge(int u, int v, int w = oo, int undir = 0) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(u, v, w));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(v, u, w * undir));
    }

    int flow() {
        int res = 0, flow;
        while((flow = dfs(s))) res += flow, ++id;
        return res;
    }

    int dfs(int u, int flow = oo) {
        if(u == t) return flow;
        vis[u] = id;

        for(auto &i: adj[u]) {
            if(vis[edges[i].v] != id && edges[i].rem()) {
                int bottleNeck = dfs(edges[i].v, min(flow, edges[i].rem()));
                edges[i].flow += bottleNeck;
                edges[i ^ 1].flow -= bottleNeck;
                if(bottleNeck) return bottleNeck;
            }
        }

        return 0;
    }
};