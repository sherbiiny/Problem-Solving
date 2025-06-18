const int N = , mod = 1e9 + 7;

int power(int a, int b) {
    int res = 1;
    while(b) {
        if(b&1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod, b >>= 1;
    }
    return res;
}

int inverse(int b) { return power(b, mod - 2); }

int fact[N], invr[N], curr, inv2 = inverse(2);
void build() {
    fact[0] = 1;
    for(int i = 1; i < N; ++i) fact[i] = 1ll*fact[i-1]*i%mod;
    invr[N - 1] = inverse(fact[N - 1]);
    for(int i = N - 2; ~i; --i) invr[i] = 1ll*invr[i + 1]*(i + 1)%mod;
}

int nPr(int n, int r) {return n<r?0:1ll*fact[n]*invr[n - r]%mod;}
int nCr(int n, int r) {return 1ll*nPr(n, r)*invr[r]%mod;}

// each query is sum of nCi [0, r]
struct Query{ int n, r, idx, t; };

void addM(int n, int m){
    curr = curr + nCr(n, m);
    if(curr >= mod) curr -= mod;
}

void remM(int n, int m) {
    curr = (curr - nCr(n, m) + mod) % mod;
}

void addN(int n, int r){
    curr = 2LL * curr - nCr(n, r);
    while(curr >= mod) curr -= mod;
    while(curr < 0) curr += mod;
}

void remN(int n, int r) {
    curr = 1ll * (nCr(n - 1, r) + curr) * inv2 % mod;
}

vector<int> MO(vector<Query> &Q, int t) {
    const int sq = sqrt(N);
    sort(Q.begin(), Q.end(),
         [&](Query &a, Query &b) {
             if(a.n/sq == b.n/sq) return a.n / sq & 1? a.r > b.r : a.r < b.r;
             return a.n/sq < b.n/sq;
         });

    int nmo = Q[0].n, rmo = 0;
    addM(nmo, 0);

    vector<int> res(t);
    for(auto &[nq, rq, iq, type]: Q){
        while(nmo < nq) addN(nmo++, rmo);
        while(nmo > nq) remN(nmo--, rmo);
        while(rmo < rq) addM(nmo, ++rmo);
        while(rmo > rq) remM(nmo, rmo--);

        res[iq] += type * curr;
        if(res[iq] < 0) res[iq] += mod;
        if(res[iq] >= mod) res[iq] -= mod;
    }

    return res;
}