// Author: _Sherbiny

#include "bits/stdc++.h"

using namespace std;
typedef long long ll;
#define endl '\n'
#define int ll

void file() {
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
    freopen("o.in", "w", stdout);
#endif
}

#define Hi ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
/////////////////////////////////////////////////////////////////////////////
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<long long>(l, r)(rng)

void magic(int tc = 0) {
    int n = getrand(1, 20);
    int k = getrand(8e8, 1e9);
    cout << n << ' ' << k << endl;
    for (int i = 0; i < n; ++i)
        cout << getrand(1e7, 1e9) << ' ';
}

signed main() {
    Hi
    int tc = 1;
    while (tc--)
        magic(tc);
}
