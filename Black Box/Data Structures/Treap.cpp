mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<long long>(l, r)(rng)

struct TreapNode {
    int sz = 1, rev = 0, key;
    ll p = getrand(1, 2e18);
    TreapNode *l = NULL, *r = NULL;
    TreapNode(int k): key(k) {};
};

using Treap = TreapNode*;

int size(Treap t) { return t? t->sz : 0; }

void prop(Treap t) {
    if(!t || !t->rev) return;
    swap(t->l, t->r);
    if(t->l) t->l->rev ^= 1;
    if(t->r) t->r->rev ^= 1;
    t->rev = 0;
}

Treap recalc(Treap t) {
    prop(t->l), prop(t->r);
    t->sz = size(t->l) + 1 + size(t->r);
    return t;
}

Treap merge(Treap l, Treap r) {
    if(!l || !r) return r ? r : l;
    prop(l), prop(r);

    if(l->p < r->p) {
        l->r = merge(l->r, r);
        return recalc(l);
    }

    r->l = merge(l, r->l);
    return recalc(r);
}

array<Treap, 2> split(Treap t, int pivot) {
    if(!t) return {NULL, NULL};
    prop(t);
    
    if(t->key > pivot) {
        auto [left, right] = split(t->l, pivot);
        t->l = right;
        return {left, recalc(t)};
    }

    auto [left, right] = split(t->r, pivot);
    t->r = left;
    return {recalc(t), right};
}

void swap(Treap &s, Treap &t, int l, int r) {
    auto [a, b] = split(s, r);
    auto [c, d] = split(a, l - 1);

    auto [e, f] = split(t, r);
    auto [i, j] = split(e, l - 1);

    s = merge(c, merge(j, b));
    t = merge(i, merge(d, f));
}

Treap answer(Treap t, int l, int r) {
    auto [a, b] = split(t, r);
    auto [c, d] = split(a, l - 1);
    cout << size(d) << endl;
    return merge(merge(c, d), b);
}

void print(Treap t) {
    if(!t) return;
    prop(t);
    print(t->l);
    // cout << t->val;
    print(t->r);
}
