struct Node {
    int val = 0, st = 0, dist = 0;
    bool isLazy = 0;

    Node() {}
    Node(int x): val(x) {}
    void add(int a, int d, int sz) {
        val += a * sz + sz * (sz - 1) / 2 * d;
        st += a, dist += d;
        isLazy = 1;
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
        Node res;
        res.val = l.val + r.val;
        return res;
    }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1 || !node[x].isLazy) return;
        node[lNode].add(node[x].st, node[x].dist, md - lx);
        node[rNode].add(node[x].st + (md - lx) * node[x].dist, node[x].dist, rx - md);
        node[x].st = node[x].dist = node[x].isLazy = 0;
    }

    void update(int l, int r, int s, int d, int x, int lx, int rx) {
        propagate(x, lx, rx);

        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r)
            return node[x].add(s + d * (lx - l), d, rx - lx);

        update(l, r, s, d, lNode, lx, md);
        update(l, r, s, d, rNode, md, rx);

        node[x] = merge(node[lNode], node[rNode]);
    }

    void update(int l, int r, int s, int d) { update(l, r, s, d, 0, 0, n); }

    Node query(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);

        if (lx >= l && rx <= r) return node[x];
        if (lx >= r || rx <= l) return Node();

        Node L = query(l, r, lNode, lx, md);
        Node R = query(l, r, rNode, md, rx);

        return merge(L, R);
    }

    Node query(int l, int r) { return query(l, r, 0, 0, n); }
};