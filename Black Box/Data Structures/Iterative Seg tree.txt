const int N = 2e5 + 1;  // limit for array size
int t[2 * N];
int m;  // array size

void build(vector<int> &v) {  // build the tree
    for (int i = 0; i < m; ++i) t[i + m] = v[i];
    for (int i = m - 1; i > 0; --i)
        t[i] = t[i << 1] + t[i << 1 | 1];
}

void modify(int p, int value) {
    for (t[p += m] = value; p > 1; p >>= 1)
        t[p >> 1] = t[p] + t[p ^ 1];
}

int query(int l, int r) {  // sum on interval [l, r)
    int res = 0;
    for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
        if (l % 2) res += t[l++];
        if (r % 2) res += t[--r];
    }
    return res;
}