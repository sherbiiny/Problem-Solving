// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1080
 
#include "bits/stdc++.h"
using namespace std;
 
typedef long long ll;
#define endl '\n'
#define int ll
//==================//
 
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
    friend mint power(ll x) {return power(mint(2), x);}
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
 
struct Comb {
    vector<mint> fact, invr;
    Comb(int n) {
        fact.assign(n + 5, 1), invr.assign(n + 5, 1);
        for (int i = 1; i <= n; ++i) fact[i]=fact[i-1]*i,invr[i]=inv(fact[i]);
    }
    mint nPr(int n, int r) {return n<r?0:fact[n]*invr[n - r];}
    mint nCr(int n, int r) {return nPr(n, r)*invr[r];}
    mint SAndBars(int n, int k) {return min(n, k)<0?0:nCr(n+k-1, k-1);}
};
 
Comb c(2000);
 
mint calc(int x, int y) {
    if((x & 1) || (y & 1)) return 0;
    x /= 2, y /= 2;
    return c.SAndBars(x, y + 1);
}
 
void magic() {
    string s; cin >> s;
    int n = s.size();
 
    mint dp[n + 2][n + 2];
    for(int i = 1; i <= n + 1; ++i) dp[i][i - 1] = 1;
 
    for(int l = n; l; --l)
        for(int r = l; r <= n; ++r)
            for(int i = l + 1; i <= r; ++i) {
                if(s[i - 1] != s[l - 1]) continue;
                dp[l][r] += dp[l + 1][i - 1] * dp[i + 1][r] * calc(i - l + 1, r - i);
            }
 
    cout << dp[1][n] << endl;
}
 
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) magic();
}
