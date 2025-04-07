// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/2431

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

void magic() {
    int k; cin >> k;
    if(k < 10) return void(cout << k << endl);

    --k;

    int x = 9, sum = 0, d = 1;
    for(; d <= 18; ++d) {
        if(sum + x * d > k) break;
        sum += x * d;
        x *= 10;
    }

    k -= sum;
    int ans = d > 1;
    for(int i = 1; i < d; ++i) ans *= 10;
    ans += k / d;

    cout << to_string(ans)[k % d] << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    cin >> t;
    while (t--) magic();
}
