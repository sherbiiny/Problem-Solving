// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1632

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

void magic() {
    int n, k; cin >> n >> k;
    vector<array<int, 2>> line;
    for(int i = 0; i < n; ++i) {
        int l, r; cin >> l >> r;
        line.push_back({r, l});
    }

    sort(line.begin(), line.end());

    multiset<int> st;
    int res = 0;
    for(auto &[r, l]: line) {
        auto it = st.upper_bound(l);
        if(it != st.begin()) st.erase(prev(it)), ++k;
        if(!k) continue;

        --k, ++res;
        st.insert(r);
    }

    cout << res << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t = 1;
    while (t--) magic();
}
