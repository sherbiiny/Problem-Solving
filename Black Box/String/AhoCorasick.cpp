// Patterns must be distinct
struct Aho {
    int N, P, A, st;
    vector<vector<int>> nxt;
    vector<int> link, out_link, out;

    Aho(int A, int st): N(0), P(0), A(A), st(st) {node();}
    int node() {
        nxt.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(-1);
        return N++;
    }

    int get (char c) {return c - st;}

    int insert(const string &p) {
        int u = 0;
        for (auto &c: p) {
            if (!nxt[u][get(c)]) nxt[u][get(c)] = node();
            u = nxt[u][get(c)];
        }

        out[u] = P;
        return P++;
    }

    void build() {
        queue <int> q;
        for (q.push(0); !q.empty();) {
            int u = q.front(); q.pop();
            for (int c = 0; c < A; ++c) {
                int v = nxt[u][c];
                if (!v) nxt[u][c] = nxt[link[u]][c];
                else {
                    link[v] = u ? nxt[link[u]][c] : 0;
                    out_link[v] = ~out[link[v]] ? link[v] : out_link[link[v]];
                    q.push(v);
                }
            }
        }
    }

    int advance (int u, char c) {
        while (u && !nxt[u][get(c)]) u = link[u];
        u = nxt[u][get(c)];
        return u;
    }
};