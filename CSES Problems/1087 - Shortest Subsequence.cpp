// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1087

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

void magic() {
    string s;
    cin >> s;

    string t = "ACGT";
    map<char, int> mp;
    int _ = 0;
    for (char ch : t) mp[ch] = _++;


    int n = int(s.size());
    vector<vector<int>> id(4);
    for (int i = 0; i < n; ++i) id[mp[s[i]]].push_back(i);


    string ans;
    for (int i = 1, last = -1; i <= n; ++i) {
        auto a = upper_bound(id[0].begin(), id[0].end(), last);
        auto b = upper_bound(id[1].begin(), id[1].end(), last);
        auto c = upper_bound(id[2].begin(), id[2].end(), last);
        auto d = upper_bound(id[3].begin(), id[3].end(), last);

        if (a == id[0].end()) {
            cout << ans + "A";
            return;
        }

        if (b == id[1].end()) {
            cout << ans + "C";
            return;
        }

        if (c == id[2].end()) {
            cout << ans + "G";
            return;
        }

        if (d == id[3].end()) {
            cout << ans + "T";
            return;
        }

        last = max({ *a, *b, *c, *d });
        ans.push_back(s[last]);
    }

    for (int i = 0; i < n + 1; ++i) cout << 'A';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
