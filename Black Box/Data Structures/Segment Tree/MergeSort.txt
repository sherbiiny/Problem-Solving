struct Node {
    vector<int> v;
    Node() {};
    Node(int x) : v({x}) {};
};

#define lNode (x * 2 + 1)
#define rNode (x * 2 + 2)
#define md (lx + (rx - lx) / 2)

struct MergeSortSagara {
    vector<Node> node;
    int n;

    MergeSortSagara(int _n) {
        n = 1;
        while (n < _n) n <<= 1;
        node.assign(n * 2, Node());
    }

    Node merge(Node &l, Node &r) {
        Node res;

        int i = 0, j = 0;
        while (i < l.v.size() && j < r.v.size()) {
            if (l.v[i] < r.v[j]) res.v.push_back(l.v[i++]);
            else res.v.push_back(r.v[j++]);
        }

        while (i < l.v.size()) res.v.push_back(l.v[i++]);
        while (j < r.v.size()) res.v.push_back(r.v[j++]);
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

    int query(int l, int r, int x, int lx, int rx, int val) {
        if (rx <= l || lx >= r) return 0;
        if (lx >= l && rx <= r) return calc(node[x], val);
        return query(l, r, lNode, lx, md, val) + query(l, r, rNode, md, rx, val);

    }

    int query(int l, int r, int val) { return query(l, r, 0, 0, n, val); }

    // change this function to match your need
    int calc(Node &no, int val) { return greater(no, val); }

    int less(Node &no, int val) {
        return lower_bound(no.v.begin(), no.v.end(), val) - no.v.begin();
    }

    int greater(Node &no, int val) {
        return no.v.size() - less(no, val + 1);
    }
};