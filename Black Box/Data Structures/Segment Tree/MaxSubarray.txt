const int oo = 2e18;

#define lNode (x * 2 + 1)
#define rNode (x * 2 + 2)
#define md (lx + (rx - lx) / 2)

// Empty subarray is not allowed
struct Sagara {
    struct Node {
        int sum = 0, pre, suf, ans;
        Node(): pre(-oo), suf(-oo), ans(-oo) {}
        Node(int x): sum(x), pre(x), suf(x), ans(x) {}
        void upd(int x) { sum = pre = suf = ans = x; }
    };

    int n;
    vector<Node> node;
    Sagara(int sz) {
        n = 1;
        while (n < sz) n *= 2;
        node.assign(n * 2, {});
    }

    Node merge(Node &l, Node &r) {
        Node res;
        res.sum = l.sum + r.sum;
        res.pre = max(l.pre, l.sum + r.pre);
        res.suf = max(r.suf, r.sum + l.suf);
        res.ans = max({l.ans, r.ans, r.pre + l.suf});
        return res;
    }

    void set(int &ind, ll &val, int x, int lx, int rx) {
        if (rx - lx == 1) return node[x].upd(val);
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