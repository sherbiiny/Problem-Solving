// Author: _Sherbiny

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

template<class T>
using minPQ = priority_queue<T, vector<T>, greater<>>;

// reverse the problem
// find the minumum cost to marge all the pieces
// always take the two smallest pieces and merge them
// HUFFMAN CODE: https://usaco.guide/CPH.pdf#page=73

void magic() {
    int n, x; cin >> x >> n;

    minPQ<int> pq;
    for(int i = 0; i < n; ++i) {
        int y; cin >> y;
        pq.push(y);
    }

    int ans = 0;
    while(pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        ans += a + b;
        pq.push(a + b);
    }

    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
