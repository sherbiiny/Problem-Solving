struct Query { int l, r, ind; };
struct MO {
    int n, sq, l, r;
    ll curr;
    vector<int> v;

    MO(vector<int> &_v) {
        v = _v;
        n = v.size();
        sq = sqrt(n) + 1;
        curr = 0;
    };

    void add(int i) {
        //
    }

    void del(int i) {
        // 
    }

    void move(int &lq, int &rq) {
        while (r < rq) add(++r);
        while (l < lq) del(l++);
        while (l > lq) add(--l);
        while (r > rq) del(r--);
    }

    void solve(vector<Query> &qu) {
        sort(qu.begin(), qu.end(), [&](auto &lf, auto ri) {
            if (lf.l / sq == ri.l / sq)
                return lf.r < ri.r;
            return lf.l / sq < ri.l / sq;
        });

        l = qu[0].l, r = qu[0].l;
        add(l);

        vector<int> res(qu.size());
        for (auto &[lq, rq, iq]: qu) {
            move(lq, rq);
            res[iq] = curr;
        }

        for (int &i: res) cout << i << endl;
    }
};