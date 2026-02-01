// Not well tested
const ll oo = 1e18 + 5, N = 1e5 + 10, maxN = 1e9 + 5;

struct Line {
    ll m, c;
    Line() : m(0), c(oo) {}
    Line(ll m, ll c) : m(m), c(c) {}
};

ll sub(ll x, Line l) { return x * l.m + l.c; }

// Persistent Li Chao
struct Node {
    // range I am responsible for
    Line line;
    Node *left = NULL, *right = NULL;

    Node() {}

    Node(ll m, ll c) {
        line = Line(m, c);
        left = right = NULL;
    }

    void extend(int l, int r) {
        if (left == NULL && l != r) {
            left = new Node();
            right = new Node();
        }
    }

    Node* copy(Node* node) {
        auto newNode = new Node;
        newNode->left = node->left;
        newNode->right = node->right;
        newNode->line = node->line;
        return newNode;
    }

    Node* add(Line toAdd, int l, int r) {
        assert(l <= r);
        int mid = (l + r) / 2;
        Node* cur = copy(this);
        if (l == r) {
            if (sub(l, toAdd) < sub(l, cur->line)) swap(toAdd, cur->line);
            return cur;
        }

        bool lef = sub(l, toAdd) < sub(l, cur->line);
        bool midE = sub(mid+1, toAdd) < sub(mid+1, cur->line);

        if(midE) swap(cur->line, toAdd);
        cur->extend(l, r);

        if(lef != midE) cur->left = cur->left->add(toAdd, l, mid);
        else cur->right = cur->right->add(toAdd, mid+1, r);

        return cur;
    }

    Node* add(Line toAdd) { return add(toAdd, 0, N - 1); }

    ll query(ll x, int l, int r) {
        int mid = (l + r) / 2;
        if (l == r || left == NULL) return sub(x, line);
        extend(l, r);
        if (x <= mid) return min(sub(x, line), left->query(x, l, mid));
        return min(sub(x, line), right->query(x, mid+1, r));
    }

    ll query(ll x) { return query(x, 0, maxN - 1); }

    void clear() {
        if (left != NULL) left->clear(), right->clear();
        delete this;
    }
};

Node* tree[N];