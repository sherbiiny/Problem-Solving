mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define getrand(l, r) uniform_int_distribution<long long>(l, r)(rng)

const int c = 2;
typedef array<int, c> H;

struct Hash {
    int mod[c], base[c];
    vector<H> pw, inv;
    int N, st;

    Hash(int _n, int _s) {
        N = _n + 1;
        st = _s - 1;
        pw.resize(N);
        inv.resize(N);
        pre();
    }

    void gen(int k) {
        auto check = [](int x) {
            for (int i = 2; i * i <= x; ++i)
                if (!(x % i)) return false;
            return true;
        };
        mod[k] = getrand(1e8, 2e9);
        base[k] = getrand(30, 120);
        while (!check(mod[k]))--mod[k];
    }

    void pre() {
        for (int k = 0; k < c; ++k) {
            gen(k);
            pw[0][k] = inv[0][k] = 1;
            int invB = power(base[k], mod[k] - 2, k);
            for (int i = 1; i < N; ++i) {
                pw[i][k] = mul(pw[i - 1][k], base[k], k);
                inv[i][k] = mul(inv[i - 1][k], invB, k);
            }
        }
    }

    vector<H> build(string &s) {
        int n = s.size();
        vector<H> hash(n);
        for (int k = 0; k < c; ++k) {
            hash[0][k] = mul(s[0] - st, pw[0][k], k);
            for (int i = 1; i < n; ++i)
                hash[i][k] = add(hash[i - 1][k], mul((s[i] - st), pw[i][k], k), k);
        }
        return hash;
    }

    H getFullHash(string &s) {
        int n = s.size();
        H res;
        for (int k = 0; k < c; ++k) {
            res[k] = mul(s[0] - st, pw[0][k], k);
            for (int i = 1; i < n; ++i)
                res[k] = add(res[k], mul((s[i] - st), pw[i][k], k), k);
        }
        return res;
    }

    // hash value of the string s[l, r] both l, r included
    H getHash(int l, int r, vector<H> &hash) {
        H res;
        for (int k = 0; k < c; ++k) {
            res[k] = hash[r][k];
            if (l) {
                res[k] = add(res[k], -hash[l - 1][k], k);
                res[k] = mul(res[k], inv[l][k], k);
            }
        }
        return res;
    }

    void concat(H &l, H &r, int lSize) {
        for (int k = 0; k < c; ++k)
            l[k] = add(l[k], mul(r[k], pw[lSize][k], k), k);
    }
    
    int add(int a, int b, int &k) {
        ll ans = (ll) a + b;
        if (ans >= mod[k]) ans -= mod[k];
        if (ans < 0) ans += mod[k];
        return ans;
    }

    int mul(int a, int b, int &k) {
        return (1ll * a * b) % mod[k];
    }

    int power(int a, int b, int &k) {
        int res = 1;
        while (b) {
            if (b & 1) res = mul(res, a, k);
            a = mul(a, a, k), b >>= 1;
        }
        return res;
    }
};