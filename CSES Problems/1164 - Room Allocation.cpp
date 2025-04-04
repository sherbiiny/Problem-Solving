// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1164

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

void magic() {
    int n; cin >> n;
    vector<int> room(n);
    set<int> free;

    vector<array<int, 3>> line;
    for(int i = 0; i < n; ++i) {
        int l, r; cin >> l >> r;
        line.push_back({l, 0, i});
        line.push_back({r, 1, i});
        free.insert(i + 1);
    }

    sort(line.begin(), line.end());
    for(auto &[x, t, i]: line) {
        if(t == 0) {
            room[i] = *free.begin();
            free.erase(free.begin());
        }
        else free.insert(room[i]);
    }

    cout << *max_element(room.begin(), room.end()) << endl;
    for(int &i: room) cout << i << ' ';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
