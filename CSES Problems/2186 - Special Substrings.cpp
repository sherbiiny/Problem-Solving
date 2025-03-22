// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/2186

#include "bits/stdc++.h"
using namespace std;
 
typedef long long ll;
#define endl '\n'
//====================//
 
void magic() {
    string s; cin >> s;
    int c = 0, n = s.length();
    vector<int> id(26, -1);
    for(char &ch: s)
        if(id[ch - 'a'] == -1) id[ch - 'a'] = c++;
 
    map<vector<int>, int> mp;
    vector<int> f(c);
    mp[f] = 1;
 
    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        f[id[s[i] - 'a']]++;
        vector<int> cnt(c);
        for(int j = 0; j < c - 1; ++j)
            cnt[j] = f[j] - f[j + 1];
        ans += mp[cnt]++;
    }
 
    cout << ans;
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
