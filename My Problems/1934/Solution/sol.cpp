// Author: _Sherbiny

#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#define endl '\n'
void Hi() {
#ifndef ONLINE_JUDGE
freopen("in.in", "r", stdin);
freopen("o.in", "w", stdout);
#endif
ios_base::sync_with_stdio(false);
cin.tie(nullptr); cout.tie(nullptr);
}
////////////////////////////////////////////////////////////

struct Node {
    ll neutral = 0;
    ll mx, sec;
    int c1, c2;

    Node() {
        mx = sec = c1 = c2 = neutral;
    }

    Node(ll x, int color) {
        mx = x;
        c1 = color;
        sec = c2 = neutral;
    }
};

struct Sagara {
    int n;
    vector<Node> node;

    Sagara(int sz) {
        n = 1;
        while(n < sz) n *= 2;
        node.assign(n * 2, Node());
    }

    Node merge(Node &l, Node &r) {
        Node res = Node();
        /*
         * list of all cases
         * l.mx > r.mx ==> res.mx = l.mx
         * r.mx > l.mx ==> res.mx = r.mx
         * r.mx = l.mx ==> res.mx??
         *
         * let's say we took res.mx = l.mx
         * then check first if r.mx > l.sec && r.c1 != l.c1 ==> take sec = r.mx
         * else we compare r.sec with l.sec
         * if r.sec > l.sec && r.c2 != l.c1 ==> take sec = r.sec
         * else take sec = l.sec (it's valid)
         * */

        if(l.mx > r.mx) {
            res.mx = l.mx;
            res.c1 = l.c1;

            if((r.mx > l.sec) && (r.c1 != res.c1)) {
                res.sec = r.mx;
                res.c2 = r.c1;
            }
            else if((r.sec > l.sec) && (r.c2 != res.c1)) {
                res.sec = r.sec;
                res.c2 = r.c2;
            }
            else {
                res.sec = l.sec;
                res.c2 = l.c2;
            }
        }

        else {
            res.mx = r.mx;
            res.c1 = r.c1;

            if((l.mx > r.sec) && (l.c1 != res.c1)) {
                res.sec = l.mx;
                res.c2 = l.c1;
            }
            else if((l.sec > r.sec) && (l.c2 != res.c1)) {
                res.sec = l.sec;
                res.c2 = l.c2;
            }
            else {
                res.sec = r.sec;
                res.c2 = r.c2;
            }
        }

        return res;
    }

    void set(int &ind, ll &val, int color, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(ind == lx) node[x] = Node(val, color);
            return;
        }

        int m = lx + (rx - lx) / 2;
        int left = x * 2 + 1;
        int right = left + 1;

        if(ind < m) set(ind, val, color, left, lx, m);
        else set(ind, val, color, right, m, rx);

        node[x] = merge(node[left], node[right]);
    }

    void set(int ind, ll val, int color) {
        set(ind, val, color, 0, 0, n);
    }

    Node query(int &l, int &r, int x, int lx, int rx) {
        if(lx >= r || rx <= l) return Node();
        if(rx <= r && lx >= l) return node[x];

        int m = lx + (rx - lx) / 2;
        int left = x * 2 + 1;
        int right = left + 1;

        Node leftPath = query(l, r, left, lx, m);
        Node rightPath = query(l, r, right, m, rx);

        return merge(leftPath, rightPath);
    }

    Node query(int l, int r) {
        return query(l, r, 0, 0, n);
    }
};

void magic(int tc = 0) {
    int n; cin >> n;

    Sagara dp(n + 1);
    ll res = 0;

    for(int i = 0; i < n; ++i) {
        int h, c, b; cin >> h >> c >> b;
        Node no = dp.query(1, h);
        ll val = (no.c1 != c? no.mx : no.sec) + b;
        dp.set(h, val, c);
        res = max(res, val);
    }

    cout << res << endl;
}

signed main() {
    Hi();
    int tc = 1; cin >> tc;
    while(tc--)
        magic(tc);
}
