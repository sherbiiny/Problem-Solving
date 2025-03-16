// O(V * E^2)
static const int oo = 2e15;

struct Edge {
    int u, v, flow = 0, cap = 0; // keep the order

    Edge(int u, int v): u(u), v(v) {}
    Edge(int u, int v, int c): u(u), v(v), cap(c) {}

    int rem() { return cap - flow; }
};

struct EdmondKarp {
    int n, s, t, id = 1;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> par;

    EdmondKarp(int n, int s, int t): n(n), s(s), t(t) {
        adj.assign(n + 1, {});
    }

    void addEdge(int u, int v, int w = oo, int undir = 0) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(u, v, w));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(v, u, w * undir));
    }

    int flow() {
        int res = 0, flow;
        while((flow = bfs())) {
            res += flow;
            int u = t;
            while(u != s) {
                edges[par[u]].flow += flow;
                edges[par[u] ^ 1].flow -= flow;
                u = edges[par[u]].u;
            }
        }
        return res;
    }

    int bfs() {
        par.assign(n + 1, -1);
        queue<array<int, 2>> q;
        q.push({s, oo});

        while(!q.empty()) {
            auto [u, flow] = q.front();
            q.pop();

            if(u == t) return flow;

            for(auto i: adj[u]) {
                auto &[u, v, f, c] = edges[i];
                if(~par[v] || !edges[i].rem()) continue;
                par[v] = i;
                q.push({v, min(flow, edges[i].rem())});
            }
        }

        return 0;
    }
};