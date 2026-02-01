struct Sagara {
    int n = 1, oo = 2e18;
    vector<int> t;

    Sagara(int sz) {
        while (n < sz) n <<= 1;
        t.assign(2 * n, oo);
    }

    void build(vector<int> &v) {
        for (int i = 0; i < size(v); ++i) t[i + n] = v[i];
        for (int i = n - 1; i > 0; --i)
            t[i] = min(t[i << 1], t[i << 1 | 1]);
    }

    void update(int p, int value) {
        for (t[p += n] = value; p > 1; p >>= 1)
            t[p >> 1] = min(t[p], t[p ^ 1]);
    }

    int query(int l, int r) {
        int res = oo;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, t[l++]);
            if (r & 1) res = min(res, t[--r]);
        }
        return res;
    }
};