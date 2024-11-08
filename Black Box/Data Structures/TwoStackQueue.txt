const int oo = 2e18;
struct TwoStackQ {
    struct Node {
        int mx = -oo, mn = oo, val;
        Node(): val(0) {}
        Node(int x): mx(x), mn(x), val(x) {}
    };

    stack<Node> a, b;

    int size() { return a.size() + b.size(); }

    void mrg(Node &a, Node &b) {
        a.mn = min(a.mn, b.mn);
        a.mx = max(a.mx, b.mx);
    }

    void push(int val) {
        auto nd = Node(val);
        if(!a.empty()) mrg(nd, a.top());
        a.push(nd);
    }

    void move() {
        while(!a.empty()) {
            auto nd = Node(a.top().val);
            if(!b.empty()) mrg(nd, b.top());
            b.push(nd), a.pop();
        }
    }

    Node get() {
        Node res;
        if(!b.empty()) mrg(res, b.top());
        if(!a.empty()) mrg(res, a.top());
        return res;
    }

    void pop() {
        if(b.empty()) move();
        if(!b.empty()) b.pop();
    }
};