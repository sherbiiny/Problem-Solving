// Author: _Sherbiny

#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define endl '\n'
void Hi() {
#ifndef ONLINE_JUDGE
freopen("in.in", "r", stdin);
freopen("o.in", "w", stdout);
#endif
ios_base::sync_with_stdio(false);
cin.tie(nullptr); cout.tie(nullptr);
}
////////////////////////////////////////////////////////////



void magic(int tc = 0) {
    int x, y; cin >> x >> y;
    cout << __gcd(x, y) << endl;
}

signed main() {
    Hi();
    int tc = 1; cin >> tc;
    while(tc--)
        magic(tc);
}
