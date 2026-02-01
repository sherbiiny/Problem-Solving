template<class T>
struct SparseTable {
    static const int B = 21;
    vector<array<T, B>> t;
    vector<int> lg;

    SparseTable(int n, vector<T> &v): t(n + 1), lg(n + 1) {
        lg[n] = __lg(n);
        for (int i = 0; i < n; ++i) lg[i] = __lg(i), t[i][0] = v[i];
        for (int j = 1; j < B; ++j)
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
                t[i][j] = merge(t[i][j - 1], t[i + (1 << j - 1)][j - 1]);
    }

    T merge(T &l, T &r) { return min(l, r); }
    T query(int l, int r) {
        int j = lg[r - l + 1];
        return merge(t[l][j], t[r - (1 << j) + 1][j]);
    }
};