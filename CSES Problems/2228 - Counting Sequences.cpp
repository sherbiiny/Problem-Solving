// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/2228

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
//====================//

const int MOD = 1e9 + 7;
struct mint {
    int value;
    mint(int v = 0) { value = v % MOD; if(value < 0) value += MOD; }
    mint(int a, int b) : value(0) { *this += a; *this /= b; }

    mint& operator+=(mint const& b) { value += b.value; if(value >= MOD) value -= MOD; return *this; }
    mint& operator-=(mint const& b) { value -= b.value; if(value < 0) value += MOD; return *this; }
    mint& operator*=(mint const& b) { value = 1ll * value * b.value % MOD; return *this; }

    friend mint power(mint a, ll e) {
        mint res = 1; while(e) { if(e & 1) res *= a; a *= a; e >>= 1; }
        return res;
    }
    friend mint inv(mint a) { return power(a, MOD - 2); }
    mint &operator/=(mint const& b) { return *this *= inv(b); }
    friend mint operator+(mint a, mint const b) { return a += b; }
    friend mint operator-(mint a, mint const b) { return a -= b; }
    friend mint operator-(mint const a) { return 0 - a; }
    friend mint operator*(mint a, mint const b) { return a *= b; }
    friend mint operator/(mint a, mint const b) { return a /= b; }
    friend ostream& operator<<(ostream& os, mint const& a) { return os << a.value; }
    friend bool operator==(mint const &a, mint const& b) { return a.value == b.value; }
    friend bool operator!=(mint const& a, mint const& b) { return a.value != b.value; }
};

const int N = 1e6 + 10;
mint fact[N], invr[N];
void build() {
    fact[0] = 1;
    for(int i = 1; i < N; ++i) fact[i]=fact[i-1]*i;
    invr[N - 1] = inv(fact[N - 1]);
    for(int i = N - 2; ~i; --i) invr[i] = invr[i + 1] * (i + 1);
}

mint nPr(int n, int r) {return n<r?0:fact[n]*invr[n - r];}
mint nCr(int n, int r) {return nPr(n, r)*invr[r];}
mint SAndBars(int n, int k) {return min(n, k)<0?0:nCr(n+k-1, k-1);}
mint catalan(int n) {return nCr(n * 2, n) / (n + 1);}

void magic() {
    build();
    int n, k; cin >> n >> k;

    // Inclusion Exclusion
    
    mint ans = 0;
    for(int leave = 0; leave <= k; ++leave) {
        mint cnt = nCr(k, leave);
        if(leave & 1) ans -= cnt * power(mint(k - leave), n);
        else ans += cnt * power(mint(k - leave), n);
    }

    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
