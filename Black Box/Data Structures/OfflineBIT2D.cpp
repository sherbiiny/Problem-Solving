template <typename T>
struct BIT2D {
    int n;
    vector<vector<int>> vals;
    vector<vector<T>> bit;

    int ind(const vector<int> &v, int x) {
        return upper_bound(begin(v), end(v), x) - begin(v) - 1;
    }

    // n: the limit of the first dimension
    // todo: all update operations you will make
    BIT2D(int n, vector<array<int, 2>> &todo): n(n + 1), vals(n + 1), bit(n + 1) {
        sort(begin(todo), end(todo), [](auto &a, auto &b) { return a[1] < b[1]; });

        for (int i = 0; i < n; i++) vals[i].push_back(-oo);
        for (auto [r, c] : todo)
            for (; r < n; r |= r + 1)
                if (vals[r].back() != c) vals[r].push_back(c);

        for (int i = 0; i < n; i++) bit[i].resize(vals[i].size());
    }

    void add(int r, int c, T val) {
        for (; r < n; r |= r + 1) {
            int i = ind(vals[r], c);
            for (; i < bit[r].size(); i |= i + 1) bit[r][i] += val;
        }
    }

    T query(int r, int c) {
        T ans = 0;
        for (; r >= 0; r = (r & r + 1) - 1) {
            int i = ind(vals[r], c);
            for (; i >= 0; i = (i & i + 1) - 1) ans += bit[r][i];
        }
        return ans;
    }

    T query(int r1, int c1, int r2, int c2) {
        return query(r2, c2) - query(r2, c1 - 1) - query(r1 - 1, c2) + query(r1 - 1, c1 - 1);
    }

    void reset() {
        for(auto &v: bit) for(auto &i: v) i = 0;
    }
};