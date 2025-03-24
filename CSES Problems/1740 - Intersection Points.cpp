// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1740

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
} tree(3e6);

const int N = 1e6 + 1;

void magic() {
    int n; cin >> n;
    vector<array<int, 4>> line;
    for(int i = 0; i < n; ++i) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        if(a == c) line.push_back({a, b, d, 1});
        else {
            line.push_back({a, b, 0, 0});
            line.push_back({c, b, 0, 2});
        }
    }

    sort(line.begin(), line.end());

    int cnt = 0;
    for(auto &[x, a, b, t]: line) {
        a += N, b += N;
        if(t == 0) tree.add(a, 1);
        else if(t == 1) cnt += tree.get(a, b);
        else tree.add(a, -1);
    }

    cout << cnt << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t = 1;
    while (t--) magic();
}
