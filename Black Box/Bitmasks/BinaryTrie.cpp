const int B = 31;
struct Trie {
    struct Node {
        array<int, 2> nxt;
        int pref = 0, end = 0;
        Node() {nxt.fill(-1);}
    };

    vector<Node> t;

    Trie(): t({ Node() }) {}

    void add(int x) {
        int v = 0;
        for(int i = B - 1; ~i; --i) {
            int c = x >> i & 1;
            if(t[v].nxt[c] == -1) {
                t[v].nxt[c] = t.size();
                t.emplace_back();
            }
            v = t[v].nxt[c];
            t[v].pref++;
        }
        t[v].end++;
    }

    int maxXor(int x) {
        int ans = 0, v = 0;
        for(int i = B - 1; ~i; --i) {
            int z = t[v].nxt[0], o = t[v].nxt[1];
            if(x >> i & 1) {
                if(~z) v = z, ans += 1ll << i;
                else v = o;
            }
            else {
                if(~o) v = o, ans += 1ll << i;
                else v = z;
            }
        }

        return ans;
    }
};