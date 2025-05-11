// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/3141

#include "bits/stdc++.h"
using namespace std;
 
typedef long long ll;
#define endl '\n'
#define int ll
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
 
const int B = 20;
const int M = 1 << B;
mint dp[M];
 
// subset contribute to its superset
void forward() {
    for (int i = 0; i < B; ++i)
        for (int m = 0; m < M; ++m)
            if (m & (1 << i))
                dp[m] += dp[m ^ (1 << i)];
}
 
// superset contribute to its subset
void forwardRev() {
    for (int i = 0; i < B; ++i)
        for (int m = M - 1; ~m; --m)
            if (m & (1 << i))
                dp[m ^ (1 << i)] += dp[m];
}
 
// remove subset contribution from superset
void backward() {
    for (int i = 0; i < B; ++i)
        for (int m = M - 1; ~m; --m)
            if (m & (1 << i))
                dp[m] -= dp[m ^ (1 << i)];
}
 
// remove superset contribution from subset
void backwardRev() {
    for (int i = 0; i < B; ++i)
        for (int m = 0; m < M; ++m)
            if (m & (1 << i))
                dp[m ^ (1 << i)] -= dp[m];
}
 
void magic() {
    int n; cin >> n;
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        dp[x] += 1;
    }
 
    forwardRev();
    for(int i = 0; i < M; ++i) dp[i] = power(mint(2), dp[i].value);
    backwardRev();
 
    for(int i = 0; i <= n; ++i) cout << dp[i] << ' ';
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}