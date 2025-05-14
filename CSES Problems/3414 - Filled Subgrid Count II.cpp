// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/3414

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

vector<int> prevSmaller(vector<int> &v) {
    int n = v.size();
    vector<int> res(n, -1);
    vector<int> st;
    for (int i = n - 1; i >= 0; --i) {
        if (st.empty() || v[i] >= v[st.back()]) st.push_back(i);
        else {
            res[st.back()] = i;
            st.pop_back();
            ++i;
        }
    }
    return res;
}

void magic() {
    int n, k; cin >> n >> k;
    vector<string> g(n);
    for(auto &s: g) cin >> s;

    vector<int> ans(k), cnt(n);

    for(int i = n - 1; ~i; --i) {
        for(int j = 0; j < n; ++j)
            cnt[j] = i + 1 < n && g[i][j] == g[i + 1][j]? cnt[j] + 1 : 1;

        auto prv = prevSmaller(cnt);

        vector<int> dp(n);
        int st = 0;
        for(int j = 0; j < n; ++j) {
            if(j && g[i][j - 1] != g[i][j]) st = j;

            dp[j] = (j - max(prv[j], st - 1)) * cnt[j];
            if(prv[j] >= st) dp[j] += dp[prv[j]];

            ans[g[i][j] - 'A'] += dp[j];
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
