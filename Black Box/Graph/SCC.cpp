struct SCC {
  int n, timer = 1, sz;
  vector<vector<int>> adj, comp, adjCC;
  vector<int> in, low, id, st;
  vector<bool> stacked;

  SCC(int n): n(n), sz(0) {};

  void build(vector<vector<int>>& _adj) {
      adj = _adj;
      in.assign(n + 1, 0);
      low.assign(n + 1, 0);
      id.assign(n + 1, 0);
      stacked.assign(n + 1, 0);

      for (int u = 1; u <= n; ++u)
          if (!in[u]) dfs(u);

      condens();
  }

  void dfs(int u) {
      in[u] = low[u] = timer++;
      stacked[u] = 1;
      st.push_back(u);

      for (int& v : adj[u]) {
          if (!in[v]) dfs(v), low[u] = min(low[u], low[v]);
          else if (stacked[v]) low[u] = min(low[u], in[v]);
      }

      if (low[u] == in[u]) {
          comp.push_back({});
          int v = -1;
          while (v != u) {
              v = st.back(), st.pop_back(), stacked[v] = 0;
              id[v] = sz;
              comp.back().push_back(v);
          }
          ++sz;
      }
  }

  void condens() {
      // new graph is zero indexed
      // BE CAREFUL OF MUTIPLE EDGES
      adjCC.assign(sz, {});
      for (int u = 1; u <= n; ++u)
          for (int& v : adj[u])
              if (id[u] != id[v])
                  adjCC[id[u]].push_back(id[v]);
  }
};
