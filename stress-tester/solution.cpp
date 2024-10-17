// Author: _Sherbiny

#include "bits/stdc++.h"

using namespace std;
typedef long long ll;
#define endl '\n'
#define int ll
#define Hi ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
////////////////////////////////////////////////////////////////

void magic() {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int &i: v) cin >> i;


    auto check = [&]() {
        int curr = 0;
        vector<int> res;
        bool can = 1, en = 0;
        for (int i = 0; i < n; ++i) {
            if (en && (i == n - 1)) break;

            if (curr + v[i] == k) {
                if (curr + v.back() != k) {
                    res.push_back(v.back());
                    curr += v.back();
                    en = 1;
                } else can = 0;
            };

            res.push_back(v[i]);
            curr += v[i];
        }

        if (can)
            cout << 1 << endl;
        return can;
    };

    sort(v.rbegin(), v.rend());
    if (check()) return;
    sort(v.begin(), v.end());
    if (!check()) cout << -1 << endl;
}

signed main() {
    Hi
    int t = 1;
    cin >> t;
    while (t--) magic();
}