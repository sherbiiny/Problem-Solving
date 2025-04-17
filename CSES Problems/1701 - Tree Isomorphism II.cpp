// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1701
// Tutorial: https://codeforces.com/blog/entry/101010

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

int n;
int treeID = 0;
vector<vector<int>> adj[2];
vector<int> sz[2], cent[2], name[2];
map<vector<int>, int> mp;

void getCent(int t, int u, int p) {
    sz[t][u] = 1;
    bool isCent = true;
    for(int &v: adj[t][u]){
        if(v == p) continue;
        getCent(t, v, u);
        sz[t][u] += sz[t][v];
        if(sz[t][v] > n / 2) isCent = false;
    }

    if(n - sz[t][u] > n / 2) isCent = false;
    if(isCent) cent[t].push_back(u);
}

void dfs(int t, int u, int p){
    vector<int> ch;
    for(int v : adj[t][u]){
        if(v == p) continue;
        dfs(t, v, u);
        ch.push_back(name[t][v]);
    }

    sort(ch.begin(), ch.end());
    if(!mp[ch]) mp[ch] = ++treeID;
    name[t][u] = mp[ch];
}

bool isIso() {
    getCent(0, 1, 0);
    getCent(1, 1, 0);

    for(auto &a: cent[0])
        for(int &b: cent[1]) {
            dfs(0, a, 0), dfs(1, b, 0);
            if(name[0][a] == name[1][b]) return true;
        }

    return false;
}

void magic() {
    mp.clear();
    cin >> n;

    auto take = [&](int t) {
        adj[t].assign(n + 1, {});
        sz[t].assign(n + 1, {});
        name[t].assign(n + 1, {});
        cent[t].clear();

        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[t][u].push_back(v);
            adj[t][v].push_back(u);
        }
    };

    take(0), take(1);

    cout << (isIso()? "YES" : "NO") << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    cin >> t;
    while (t--) magic();
}
