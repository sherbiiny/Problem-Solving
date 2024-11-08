// Author: _Sherbiny

#include "bits/stdc++.h"
using namespace std;

#ifdef DBG
#include "./debug.h"
#else
#define dbg(...)
#endif

typedef long long ll;
#define endl '\n'
#define int ll
//==================//

struct Node {
    int ign = 0, val;

    Node() : val(ign) {};

    Node(int x) : val(x) {};

    void set(int x) {
        val = x;
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
        Node res = Node();
        res.val = max(l.val, r.val);
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
        if (lx >= r || rx <= l) return Node(-2e18);
        if (rx <= r && lx >= l) return node[x];

        Node L = query(l, r, lNode, lx, md);
        Node R = query(l, r, rNode, md, rx);

        return merge(L, R);
    }

    Node query(int l, int r) {
        return query(l, r, 0, 0, n);
    }
};


void magic() {
    int n, m, d; cin >> n >> m >> d;
    vector<array<int, 3>> v(m);
    for(auto &[t, a, b]: v)
        cin >> a >> b >> t;

    sort(v.begin(), v.end());

    Sagara dp(n + 2);

    for(int x = 1; x <= n; ++x) {
        int gain = v[m - 1][2] - abs(x - v[m - 1][1]);
        dp.set(x, gain);
    }

    for(int i = m - 2; i >= 0; --i) {
        Sagara newDp(n + 2);
        for(int x = 1; x <= n; ++x) {
            int timeDiff = v[i + 1][0] - v[i][0];
            int l = max(1ll, x - d * timeDiff);
            int r = min(n, x + d * timeDiff);
            int gain = v[i][2] - abs(x - v[i][1]);
            int me = dp.query(l, r + 1).val + gain;
            newDp.set(x, me);
        }

        swap(dp, newDp);
    }

    cout << dp.query(1, n + 1).val << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) magic();
}