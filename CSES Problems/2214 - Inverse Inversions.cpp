// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/2214

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

struct Node {
    int ign = 0, val;
    Node() : val(ign) {};
    void set(int x) { val = x; }
};

#define lNode (x * 2 + 1)
#define rNode (x * 2 + 2)
#define md (lx + (rx - lx) / 2)

struct Sagara {
    int n;
    vector<Node> node;

    Sagara(int sz) {
        n = 1;
        while (n < sz) n *= 2;
        node.assign(n * 2, Node());
    }

    Node merge(Node &l, Node &r) {
        auto res = Node();
        res.val = l.val + r.val;
        return res;
    }

    void set(int &ind, ll &val, int x, int lx, int rx) {
        if (rx - lx == 1) return node[x].set(val);
        if (ind < md) set(ind, val, lNode, lx, md);
        else set(ind, val, rNode, md, rx);
        node[x] = merge(node[lNode], node[rNode]);
    }

    void set(int ind, ll val) { set(ind, val, 0, 0, n); }

    int kthOne(int k, int x, int lx, int rx) {
        if(rx - lx == 1) return lx;
        if(node[lNode].val >= k) return kthOne(k, lNode, lx, md);
        return kthOne(k - node[lNode].val, rNode, md, rx);
    }

    int kthOne(int k) { return kthOne(k, 0, 0, n); }
};


void magic() {
    int n, k; cin >> n >> k;

    Sagara tree(n + 1);
    for(int i = 1; i <= n; ++i) tree.set(i, 1);

    for(int i = 0; i < n; ++i) {
        int rem = n - i;
        int x = tree.kthOne(min(k + 1, rem));
        tree.set(x, 0);
        k -= min(k, rem - 1);

        cout << x << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t = 1;
    while (t--) magic();
}
