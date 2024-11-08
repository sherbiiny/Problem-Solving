// Author: _Sherbiny

#include "bits/stdc++.h"
using namespace std;

#ifdef DBG
#include "./debug.h"
#else
#define dbg(...)
#endif

typedef long long ll;
#define endl '\n'
#define int ll
//==================//

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<long long>(l, r)(rng)

void magic() {
    int n = getrand(1, 1.5e3);
    int m = getrand(1, 5);
    int d = getrand(1, n);

    cout << n << ' ' << m << ' ' << d << endl;

    while(m--) {
        cout << getrand(1, n) << ' ' << getrand(1, 1e9) << ' ' << getrand(1, 1e9) << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) magic();
}
