// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1188

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

struct Node {
    int ign = 0, sum = 0, pref = 0, suff = 0, ans = 0;

    Node() {};

    Node(int x) : sum(x), pref(x), suff(x) {};

    void set(int x) {
        sum = pref = suff = x;
    }
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
        res.sum  = l.sum + r.sum;
        res.pref = max(l.pref, l.sum + r.pref);
        res.suff = max(r.suff, r.sum + l.suff);
        res.ans  = max({l.ans, r.ans, l.suff + r.pref});
        return res;
    }

    void set(int &ind, ll &val, int x, int lx, int rx) {
        if (rx - lx == 1) return node[x].set(val);
        if (ind < md) set(ind, val, lNode, lx, md);
        else set(ind, val, rNode, md, rx);
        node[x] = merge(node[lNode], node[rNode]);
    }

    void set(int ind, ll val) { set(ind, val, 0, 0, n); }

    Node query(int &l, int &r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return Node();
        if (rx <= r && lx >= l) return node[x];
        Node L = query(l, r, lNode, lx, md);
        Node R = query(l, r, rNode, md, rx);
        return merge(L, R);
    }

    Node query(int l, int r) { return query(l, r, 0, 0, n); }
};


void magic() {
    string s; cin >> s;
    int n = s.size();
    array tree{Sagara(n), Sagara(n)};

    for(int i = 0; i < n; ++i) {
        tree[s[i] - '0'].set(i, 1);
        tree[!(s[i] - '0')].set(i, -n);
    }

    int q; cin >> q;
    while(q--) {
        int i; cin >> i;
        --i;

        s[i] = s[i] - '0'? '0' : '1';
        tree[s[i] - '0'].set(i, 1);
        tree[!(s[i] - '0')].set(i, -n);

        cout << max(tree[0].node[0].ans, tree[1].node[0].ans) << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t = 1;
    while (t--) magic();
}
