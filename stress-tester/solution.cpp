// Author: _Sherbiny

#include "bits/stdc++.h"
using namespace std;
using ll = long long;
#define endl '\n'
//====================//
const int N = 1e6 + 10;
unordered_map<int, int> cnt[N];

vector<int> pr, low;
void Sieve(int n) {
    low.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (!low[i]) pr.push_back(low[i] = i);
        for (int &j: pr) {
            if (j > low[i] || i * j > n) break;
            low[j * i] = j;
        }
    }
}

void magic() {
    int n, x; cin >> n >> x;
    vector<int> v(n);
    for(int &i: v) cin >> i;
    sort(v.begin(), v.end());

    vector<array<int, 2>> a{{v[0], 1}};
    for(int i = 1; i < n; ++i) {
        if(v[i] == v[i - 1]) ++a.back()[1];
        else a.push_back({v[i], 1});
    }

    auto upd = [&](int md, int &y, int &f) {
        function<void(int, int)> go = [&](int r, int z) {
            if(r == 1) {
                cnt[md][z] += f;
                return;
            }
            go(r / low[r], z * low[r]);
            go(r / low[r], z);
        };

        go(y, 1);
    };

    ll ans = 0;
    for(auto &[y, f]: a) {
        int g = gcd(x, y), z = x / g, need = (x - y % x) % x;
        ans += 1ll * f * cnt[need][z];
        if(!(y * 2 % x) && !(1ll * y * y % x))
            ans += 1ll * f * (f - 1) / 2;
        upd(y % x, g, f);
    }

    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    Sieve(N);
    int t = 1;
    while (t--) magic();
}
