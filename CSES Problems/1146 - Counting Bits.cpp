// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1146

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//
 
// count the number of times the k-th bit is set in the range [0, n]
int count_kth_bit(int n, int k) {
    ++n;
    int d = (1LL << (k + 1)), p = (1LL << k);
    return n / d * p + max(0LL, n % d - p);
}
 
void magic() {
    int n; cin >> n;
    int res = 0;
    for(int i = 0; (1ll << i) <= n; ++i)
        res += count_kth_bit(n, i);
      
    cout << res << endl;
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    int t = 1;
    while (t--) magic();
}