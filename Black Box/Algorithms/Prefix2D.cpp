// One indexed
struct Prefix2D {
    int n, m;
    vector<vector<int>> g;

    Prefix2D(int n, int m, auto &g): g(g), n(n), m(m) { build(); }
    Prefix2D(int n, int m): n(n), m(m), g(n + 2, vector<int>(m + 2)) {}

    // (a, b) to (c, d)
    void add(int a, int b, int c, int d, int val = 1) {
        g[a][b] += val, g[c + 1][d + 1] += val;
        g[a][d + 1] -= val, g[c + 1][b] -= val;
    }

    // build twice for partial sum
    void build() {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                g[i][j] += g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1];
    }

    int get(int a, int b, int c, int d) {
        return g[c][d] - g[a - 1][d] - g[c][b - 1] + g[a - 1][b - 1];
    }
};
