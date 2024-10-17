// Author: _Sherbiny

#include "bits/stdc++.h"

using namespace std;
typedef long long ll;
#define endl '\n'
#define int ll
#define Hi ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
////////////////////////////////////////////////////////////////

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<long long>(l, r)(rng)

void magic() {
    cout << 1 << endl;
    int n = getrand(1, 100), k = getrand(1, 200);
    cout << n << ' ' << k << endl;
    for (int i = 0; i < n; ++i)
        cout << getrand(1, k) << ' ';
}

signed main() {
    Hi
    int t = 1;
    while (t--) magic();
}