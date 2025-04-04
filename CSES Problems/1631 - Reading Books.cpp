// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1147

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

void magic() {
    int n; cin >> n;
    int sm = 0, mx = 0;
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        sm += x, mx = max(mx, x);
    }

    cout << sm + max(0ll, mx * 2 - sm) << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
