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

int a[27];
int n, k;

int go(int i, int curr) {
    if (i == n) return curr ? 1e9 : 0;
    return min(go(i + 1, curr), go(i + 1, curr * a[i] % k) + 1);
}

void magic(int tc = 0) {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int res = go(0, 1);
    cout << (res >= 1e9? -1 : res) << endl;
}

signed main() {
    Hi
    int tc = 1;
    while (tc--)
        magic(tc);
}
