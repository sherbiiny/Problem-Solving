// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/3223/

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

struct BIT {
    int n;
    vector<int> t;

    BIT(int n): n(n), t(n + 1) {}

    void add(int i, int x) {
        for(; i < n; i |= i + 1) t[i] += x;
    }

    int get(int i) {
        int res = 0;
        for(; i >= 0; i = (i & i + 1) - 1) res += t[i];
        return res;
    }

    int get(int l, int r) { return get(r) - get(l - 1); }
};

vector<int> compress(vector<int> &a) {
    int n = a.size();
    map<int, int> mp;
    for(int &i: a) mp[i];
    vector<int> res(n);
    int c = 0;
    for(auto &[i, _]: mp) mp[i] = c++;
    for(int i = 0; i < n; ++i) res[i] = mp[a[i]];
    return res;
}

void magic() {
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(int &i: v) cin >> i;
    v = compress(v);

    BIT tree(n + 2);
    int cnt = 0;
    auto add = [&](int x) {
        x = v[x];
        cnt += tree.get(x + 1, n);
        tree.add(x, 1);
    };

    auto rem = [&](int x) {
        x = v[x];
        cnt -= tree.get(x - 1);
        tree.add(x, -1);
    };

    for(int i = 0; i < k - 1; ++i) add(i);

    for(int i = k - 1; i < n; ++i) {
        add(i);
        cout << cnt << ' ';
        rem(i - k + 1);
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
