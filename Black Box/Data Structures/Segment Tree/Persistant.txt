struct Node {
    Node *l, *r;
    int val = 0;

    Node(int val): l(NULL), r(NULL), val(val) {}
    Node(): l(NULL), r(NULL) {}
    Node(Node *l, Node *r): l(l), r(r) {
        if (l != NULL) val += l->val;
        if (r != NULL) val += r->val;
    }

    void addChild() {
        l = new Node();
        r = new Node();
    }
};

struct PST {
    int n;
    PST(int n): n(n + 1) {}

    Node merge(Node x, Node y) {
        Node ret;
        ret.val = x.val + y.val;
        return ret;
    }

    Node *set(Node *v, int i, int val, int lx, int rx) {
        if (lx == rx) return new Node(val);
        int mid = (lx + rx) / 2;
        if(!v->l) v->addChild();
        if (i <= mid) return new Node(set(v->l, i, val, lx, mid), v->r);
        return new Node(v->l, set(v->r, i, val, mid + 1, rx));
    }

    Node *set(Node *v, int i, int val) { return set(v, i, val, 0, n - 1); }

    // [l, r] r is included
    Node query(Node *v, int l, int r, int lx, int rx) {
        if (l > rx || r < lx) return {};
        if (l <= lx && r >= rx) return *v;
        if(!v->l) v->addChild();
        int mid = (lx + rx) / 2;
        return merge(query(v->l, l, r, lx, mid), query(v->r, l, r, mid + 1, rx));
    }

    Node query(Node *v, int l, int r) { return query(v, l, r, 0, n - 1); }

    int getKth(Node *a, Node *b, int k, int lx, int rx) {
        if (lx == rx) return lx;
        if(!a->l) a->addChild();
        if(!b->l) b->addChild();
        int rem = b->l->val - a->l->val;
        int mid = (lx + rx) / 2;
        if (rem >= k) return getKth(a->l, b->l, k, lx, mid);
        return getKth(a->r, b->r, k - rem, mid + 1, rx);
    }

    int getKth(Node *a, Node *b, int k) { return getKth(a, b, k, 0, n - 1); }
};