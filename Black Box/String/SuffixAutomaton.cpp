struct SuffixAutomaton {
    static const int A = 26;

    struct State {
        int len = 0, lnk = -1, cnt = 0, d = 1;
        int firstPos = 0, sum = 0; // if you need
        bool isClone = 0;
        array<int, A> nxt;
        State() { nxt.fill(-1); }
    };

    vector<State> t{{}};
    int lst = 0;

    SuffixAutomaton(string &s) {
        for(char &ch: s) insert(ch);
    }

    void insert(int ch) {
        int c = ch - 'a', me = t.size(), p = lst;
        t.push_back({});
        t[me].len = t[p].len + 1;
        t[me].firstPos = t[me].len - 1;
        t[me].cnt = 1;
        t[me].lnk = 0;
        lst = me;

        while(~p && t[p].nxt[c] == -1) {
            t[p].nxt[c] = me;
            p = t[p].lnk;
        }

        if(p == -1) return;

        int q = t[p].nxt[c];
        if(t[q].len == t[p].len + 1) {
            t[me].lnk = q;
            return;
        }

        int clone = t.size();
        t.push_back(t[q]);

        t[clone].len = t[p].len + 1;
        t[clone].isClone = 1;
        t[clone].cnt = 0;

        while (~p && t[p].nxt[c] == q) {
            t[p].nxt[c] = clone;
            p = t[p].lnk;
        }

        t[q].lnk = t[me].lnk = clone;
    }

    int move(int v, char &c) { return ~v? t[v].nxt[c - 'a'] : -1; }

    void move(int &v, int &len, char &c) {
        while(move(v, c) == -1) {
            v = t[v].lnk;
            if(v == -1) break;
            len = t[v].len;
        }

        if(~v) v = move(v, c), ++len;
        else v = 0;
    }

    int distinctSubstrings(){
        int ans = 0;
        for(int i = 1; i < t.size(); i++)
            ans += t[i].len - t[t[i].lnk].len;
        return ans;
    }

    int lenOfDistinctSubstrings() {
        int ans = 0;
        for(int i = 1; i < t.size(); i++) {
            int mn = t[t[i].lnk].len + 1, mx = t[i].len;
            ans += (mx - mn + 1) * (mx + mn) / 2;
        }
        return ans;
    }

    void preCount() {
        vector<array<int, 2>> v;
        for(int i = 0; i < t.size(); ++i)
            v.push_back({t[i].len, i});

        sort(v.rbegin(), v.rend());
        for(auto &[_, i]: v) {
            t[i].sum = t[i].cnt;
            if(i) t[t[i].lnk].cnt += t[i].cnt;
            for(int &to: t[i].nxt) if(~to) {
                t[i].d += t[to].d;
                t[i].sum += t[to].sum;
            }
        }
    }

    int countOcc(string &p) {
        int v = 0;
        for(int i = 0; i < p.size(); ++i) {
            v = move(v, p[i]);
            if(v == -1) return 0;
        }
        return t[v].cnt;
    }

    string kthDistinct(int k) {
        int v = 0;
        string ans;

        while(~v && k) {
            k--;
            int nxt = -1, add = 0;
            for(int i = 0; i < A; ++i) {
                int to = t[v].nxt[i];
                if(to == -1) continue;

                nxt = to, add = i;
                if(k - t[to].d < 0) break;
                k -= t[to].d;
            }

            if(nxt == -1) break;
            ans += char(add + 'a');
            v = nxt;
        }

        return k? "" : ans;
    }

    string kth(int k) {
        int v = 0;
        string ans;

        while(k > 0) {
            int nxt = -1, add = 0;
            for(int i = 0; i < A; ++i) {
                int to = t[v].nxt[i];
                if(to == -1) continue;

                nxt = to, add = i;
                if(k - t[to].sum <= 0) break;
                k -= t[to].sum;
            }

            if(nxt == -1) break;

            ans += char(add + 'a');
            v = nxt;
            k -= t[v].cnt;
        }

        return k > 0? "" : ans;
    }

    int LCS(string &s) {
        int v = 0, ans = 0, len = 0;
        for(char &ch: s) {
            move(v, len, ch);
            ans = max(ans, len);
        }
        return ans;
    }
};