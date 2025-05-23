// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1624/

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//
const int n = 8;

void magic() {
    vector bad(n, vector<int>(n));
    vector<int> col(n), diaS(n * 2), diaM(n * 2);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            char c; cin >> c;
            bad[i][j] = c == '*';
        }

    // each row must have exactly one queen
    // for each row try all valid position of the queen
    auto go = [&](auto &&go, int i) -> int {
        if(i == n) return 1;

        int res = 0;
        for(int j = 0; j < n; ++j) {
            if(bad[i][j] || col[j] || diaS[i + j] || diaM[i - j + n]) continue;
            col[j] = diaS[i + j] = diaM[i - j + n] = 1;
            res += go(go, i + 1);
            col[j] = diaS[i + j] = diaM[i - j + n] = 0;
        }

        return res;
    };

    cout << go(go, 0) << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
