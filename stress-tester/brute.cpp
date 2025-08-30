// Author: _Sherbiny

#include "bits/stdc++.h"
using namespace std;
using ll = long long;
#define endl '\n'
#define int ll
//====================//
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<long long>(l, r)(rng)

vector<int> v;
int count(int x) {
    int ans = 0;
    for(int i = 0; i < size(v); ++i)
        for(int j = i + 1; j < size(v); ++j) {
            if(!((v[i] + v[j]) % x) && !(v[i] * v[j] % x))
                ++ans;
        }

    return ans;
}

void magic() {
    int n, x; cin >> n >> x;
    v.resize(n);
    for(int &i: v) cin >> i;
    cout << count(x) << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t = 1;
    while (t--) magic();
}
