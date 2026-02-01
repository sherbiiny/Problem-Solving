vector<vector<int>> rotate90(vector<vector<int>> &g) {
    int n = g.size(), m = g[0].size();
    vector res(m, vector<int>(n));
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
            res[i][j] = g[n - j - 1][i];
    return res;
}