struct Node {
    int ign = 0, lazy = 0, val = ign;
    bool isLazy = 0;

    Node() {}

    Node(ll x) : val(x) {}

    void add(int x, int lx, int rx) {
        val += x * (rx - lx);
        lazy += x;
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
        Node res = Node();
        res.val = l.val + r.val;
        return res;
    }

    void build(vector<int> &v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < v.size()) node[x] = Node(v[lx]);
            return;
        }

        build(v, lNode, lx, md);
        build(v, rNode, md, rx);
        node[x] = merge(node[lNode], node[rNode]);
    }

    void build(vector<int> &v) { build(v, 0, 0, n); }

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1 || !node[x].isLazy) return;

        node[lNode].add(node[x].lazy, lx, md);
        node[rNode].add(node[x].lazy, md, rx);

        node[x].isLazy = node[x].lazy = 0;
    }

    void update(int l, int r, ll val, int x, int lx, int rx) {
        propagate(x, lx, rx);

        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r)
            return node[x].add(val, lx, rx);

        update(l, r, val, lNode, lx, md);
        update(l, r, val, rNode, md, rx);

        node[x] = merge(node[lNode], node[rNode]);
    }

    void update(int l, int r, ll val) { update(l, r, val, 0, 0, n); }

    Node query(int l, int r, int x, int lx, int rx) {
        propagate(x, lx, rx);

        if (lx >= l && rx <= r) return node[x];
        if (lx >= r || rx <= l) return Node();

        Node L = query(l, r, lNode, lx, md);
        Node R = query(l, r, rNode, md, rx);

        return merge(L, R);
    }

    Node query(int l, int r) {
        return query(l, r, 0, 0, n);
    }
};