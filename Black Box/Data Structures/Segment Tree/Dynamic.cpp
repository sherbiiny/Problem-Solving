struct TreeNode {
    int sum = 0, lazy = 0, isLazy = 0;
    TreeNode *left = nullptr, *right = nullptr;

    TreeNode() {}
    TreeNode(int x): sum(x) {}
    TreeNode(TreeNode *&a, TreeNode *&b): left(a), right(b) {}

    void update(int x, int lx, int rx) {
        sum += x * (rx - lx);
        lazy += x, isLazy = 1;
    }
};

using Node = TreeNode*;

struct DynamicSagara {
    Node root = new TreeNode();
    const int n;

    DynamicSagara(int n): n(n) {}

    Node merge(Node &a, Node &b) {
        auto res = new TreeNode(a, b);
        res->sum = a->sum + b->sum;
        return res;
    }

    void propagate(Node &cur, int lx, int rx) {
        int m = (lx + rx) / 2;
        if (cur->left == nullptr) cur->left = new TreeNode(); // l -> m
        if (cur->right == nullptr) cur->right = new TreeNode(); // m -> r
        if (!cur->isLazy) return;

        cur->left->update(cur->lazy, lx, m);
        cur->right->update(cur->lazy, m, rx);

        cur->lazy = cur->isLazy = 0;
    }

    void update(int &l, int &r, int &val, Node &node, int lx, int rx) {
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) return node->update(val, lx, rx);
        propagate(node, lx, rx);

        int m = (lx + rx) / 2;
        update(l, r, val, node->left, lx, m);
        update(l, r, val, node->right, m, rx);

        node = merge(node->left, node->right);
    }

    Node query(int l, int r, Node &node, int lx, int rx) {
        if (lx >= r || rx <= l) return new TreeNode();
        if (lx >= l && rx <= r) return node;
        propagate(node, lx, rx);

        int m = (lx + rx) / 2;
        Node L = query(l, r, node->left, lx, m);
        Node R = query(l, r, node->right, m, rx);
        return merge(L, R);
    }

    void update(int l, int r, int val) { update(l, r, val, root, 0, n); }

    Node query(int l, int r) { return query(l, r, root, 0, n); }
};
