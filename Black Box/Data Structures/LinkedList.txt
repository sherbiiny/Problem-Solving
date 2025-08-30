extern struct Node *const EMPTY;
struct Node {
    Node *l, *r;
    int val = 0;
    Node(int val = 0): l(EMPTY), r(EMPTY), val(val) {}
    Node(Node *l, Node *r): l(l), r(r) {}
} *const EMPTY = new Node(EMPTY, EMPTY);

// insert b after a
void insert(Node *a, Node *b) {
    a->r->l = b;
    b->r = a->r;
    a->r = b;
    b->l = a;
}

// delete a and return its right
Node *del(Node *a) {
    a->r->l = a->l;
    a->l->r = a->r;
    auto ret = a->r;
    return ret;
}