// Author: _Sherbiny

#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define endl '\n'
#define int ll
//==================//

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<long long>(l, r)(rng)

const int N = 100;
void magic() {
    cout << N << ' ' << 12 << endl;
    for(int i = 0; i < N; ++i)
        cout << getrand(1, 100) << ' ';
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) magic();
}
