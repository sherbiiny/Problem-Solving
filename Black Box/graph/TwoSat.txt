// Zero indexed
struct TwoSat {
    int n, timer = 1;
    vector<vector<int>> adj, comp;
    vector<int> in, low, id, st;
    vector<bool> stacked, vis;

    TwoSat(int count) {
        n = 2 * count;
        adj.assign(n, {});
    }

    int addVar() {
        adj.push_back({});
        adj.push_back({});
        n += 2;
        return n / 2 - 1;
    }

    bool solve() {
        in.assign(n, 0);
        low.assign(n, 0);
        id.assign(n, 0);
        vis.assign(n, 0);
        stacked.assign(n, 0);

        for (int i = 0; i < n; ++i)
            if (!in[i]) tarjan(i);

        for (int i = 0; i < n - 1; i += 2)
            if(id[i] == id[neg(i)]) return 0;

        return 1;
    }

    int neg(int u) { return u ^ 1; }

    // u or v or both
    void OR(int u, bool neg_u, int v, bool neg_v) {
        u = 2 * u ^ neg_u, v = 2 * v ^ neg_v;
        adj[neg(u)].push_back(v);
        adj[neg(v)].push_back(u);
    }

    // u or v but not both
    void XOR(int u, int v) {
        OR(u, 0, v, 0);
        OR(u, 1, v, 1);
    }

    void must(int u, bool neg = 0) { OR(u, neg, u, neg); }

    // if u then must v
    void implies(int u, bool neg_u, int v, bool neg_v) { OR(u, !neg_u, v, neg_v); }

    // (1, 1, 1, 1, 1, 0) || (1, 1, 1, 1, 1, 1)
    void allExpectAtMostOne(vector<int> &v){
        OR(v[0], 0, addVar(), 1);
        for(int i = 1; i < v.size(); i++){
            int me = addVar();
            OR(v[i], 0, me, 1);
            OR(v[i], 0, me - 1, 0);
            OR(me - 1,0,  me, 1);
        }
    }

    // (0, 0, 0, 0, 0, 1) || (0, 0, 0, 0, 0, 0)
    void atMostOne(vector<int> &v) {
        OR(v[0], 1, addVar(), 0);
        for(int i = 1; i < v.size(); i++) {
            int me = addVar();
            OR(v[i], 1, me, 0);
            OR(v[i], 1, me - 1, 1);
            OR(me - 1, 1, me, 0);
        }
    }

    void tarjan(int u) {
        in[u] = low[u] = timer++;
        stacked[u] = 1;
        st.push_back(u);

        for (int& v : adj[u]) {
            if (!in[v]) tarjan(v), low[u] = min(low[u], low[v]);
            else if (stacked[v]) low[u] = min(low[u], in[v]);
        }

        if (low[u] == in[u]) {
            comp.push_back({});
            int v = -1;
            while (v != u) {
                v = st.back(), st.pop_back(), stacked[v] = 0;
                comp.back().push_back(v);
                id[v] = comp.size() - 1;
            }
        }
    }

    // Zero indexed
    vector<int> get_vals() {
        vector<int> take(comp.size());
        for (int i = 0; i < comp.size(); ++i) {
            if(take[i]) continue;
            take[i] = 1;
            take[id[neg(comp[i].front())]] = -1;
        }

        vector<int> ans(n / 2);
        for (int i = 0; i < n / 2; ++i)
            ans[i] = take[id[2 * i]] == 1;
        return ans;
    }
};