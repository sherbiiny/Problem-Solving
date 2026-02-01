// get any set of edges to achieve the min cut (max flow)
vector<array<int, 2>> getEdges() {
    vector<int> srcSide(n + 1);
    queue<int> q;
    q.push(s), srcSide[s] = 1;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(auto &i: adj[u]) {
            auto &[_, v, f, c] = edges[i];
            if(!srcSide[v] && f != c) q.push(v), srcSide[v] = 1;
        }
    }

    vector<array<int, 2>> res;
    for(int i = 0; i < edges.size(); i += 2) {
        auto &[u, v, f, c] = edges[i];
        if(srcSide[u] != srcSide[v] && c != oo) res.push_back({u, v});
    }

    return res;
}