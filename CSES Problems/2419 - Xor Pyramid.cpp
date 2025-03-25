// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/2419

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

// Parity of nCr
int nCr(int n, int r) { return (n & r) == r; }

void magic() {
    int n; cin >> n;

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        ans ^= nCr(n - 1, i) * x;
    }

    cout << ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
