// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1644/

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

template<class T>
struct SparseTable {
    // change mxLog
    static const int mxLog = 21;
    vector<array<T, mxLog>> table;
    vector<int> lg;
    int n;

    SparseTable(int sz) {
        n = sz;
        table.resize(n + 1);
        lg.resize(n + 1);
        for (int i = 0; i <= n; ++i) lg[i] = __lg(i);
    }

    void build(vector<T> &v) {
        for (int i = 0; i < n; ++i) table[i][0] = v[i];
        for (int j = 1; j < mxLog; ++j)
            for (int i = 0; i + (1 << j) - 1 < n; ++i)
                table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }

    T merge(T &l, T &r) {
        return min(l, r);
    }

    T query(int l, int r) {
        int j = lg[r - l + 1];
        return merge(table[l][j], table[r - (1 << j) + 1][j]);
    }
};

void magic() {
    int n, a, b; cin >> n >> a >> b;
    vector<int> pref(n + 1);
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        pref[i] = pref[i - 1] + x;
    }

    SparseTable<int> sp(n + 1);
    sp.build(pref);

    int res = -2e18;
    for(int i = a; i <= n; ++i) {
        int l = max(0ll, i - b), r = max(0ll, i - a);
        res = max(res, pref[i] - sp.query(l, r));
    }

    cout << res << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
