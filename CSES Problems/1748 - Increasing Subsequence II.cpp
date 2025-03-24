// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1748

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

const int mod = 1e9 + 7;
struct BIT {
    int n;
    vector<int> t;

    BIT(int n): n(n), t(n + 1) {}

    void add(int i, int x) {
        for(; i < n; i |= i + 1) {
            t[i] += x;
            if(t[i] >= mod) t[i] -= mod;
        }
    }

    int get(int i) {
        int res = 0;
        for(; i >= 0; i = (i & i + 1) - 1) {
            res += t[i];
            if(res >= mod) res -= mod;
        }
        return res;
    }
};

void magic() {
    int n; cin >> n;
    vector<int> v(n);

    map<int, int> mp;
    for(int &i: v) cin >> i, mp[i];

    int c = 1;
    for(auto &[i, j]: mp) j = c++;

    BIT tree(c + 10);
    tree.add(0, 1);

    for(int i = 0; i < n; ++i) {
        int me = tree.get(mp[v[i]] - 1);
        tree.add(mp[v[i]], me);
    }

    cout << (tree.get(c + 2) - 1 + mod) % mod;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t = 1;
    while (t--) magic();
}
