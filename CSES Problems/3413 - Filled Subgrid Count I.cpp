// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/3413/

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

int dx[] = {0, 1, 1};
int dy[] = {1, 0, 1};

void magic() {
    int n, k; cin >> n >> k;
    vector<string> g(n);
    for(auto &s: g) cin >> s;

    vector dp(n, vector<int>(n));
    vector<int> ans(k), cnt(n);

    for(int i = n - 1; ~i; --i) {
        for(int j = n - 1; ~j; --j) {
            int mn = n * n + 1;

            for(int o = 0; o < 3; ++o) {
                int ni = i + dx[o], nj = j + dy[o];
                if(ni == n || nj == n || g[i][j] != g[ni][nj]) mn = 0;
                else mn = min(mn, dp[ni][nj]);
            }

            dp[i][j] = 1 + mn;
            ans[g[i][j] - 'A'] += dp[i][j];
        }
    }

    for(int &i: ans) cout << i << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
