// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1655

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//
 
const int B = 31;
struct Trie {
    struct Node {
        array<int, 2> nxt;
        int pref = 0, end = 0;
        Node() {nxt.fill(-1);}
    };
 
    vector<Node> node;
 
    Trie(): node({ Node() }) {}
 
    void add(int x) {
        int v = 0;
        for(int i = B - 1; ~i; --i) {
            int c = x >> i & 1;
            if(node[v].nxt[c] == -1) {
                node[v].nxt[c] = node.size();
                node.emplace_back();
            }
            v = node[v].nxt[c];
            node[v].pref++;
        }
        node[v].end++;
    }
 
    int maxXor(int x) {
        int ans = 0, v = 0;
        for(int i = B - 1; ~i; --i) {
            int z = node[v].nxt[0], o = node[v].nxt[1];
            if(x >> i & 1) {
                if(~z) v = z, ans += 1ll << i;
                else v = o;
            }
            else {
                if(~o) v = o, ans += 1ll << i;
                else v = z;
            }
        }
 
        return ans;
    }
};
 
void magic() {
    int n; cin >> n;
 
    Trie t;
    int pref = 0, ans = 0;
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        t.add(pref);
        pref ^= x;
        ans = max(ans, t.maxXor(pref));
    }
 
    cout << ans << endl;
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}