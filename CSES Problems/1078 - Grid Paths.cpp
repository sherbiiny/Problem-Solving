// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1078

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

const int N = 2e6 + 1;
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
    int m, n; cin >> m >> n;
    vector<array<int, 2>> v(n);
    for(auto &[x, y]: v) cin >> x >> y;
    v.push_back({1, 1});
    v.push_back({m, m});
    sort(v.begin(), v.end());
    n += 2;

    auto get = [&](int i, int j) {
        int dx = v[j][0] - v[i][0];
        int dy = v[j][1] - v[i][1];
        if(min(dx, dy) < 0) return mint(0);
        return SAndBars(dx, dy + 1);
    };

    mint dp[n][2];
    dp[n - 1][0] = 1;
    dp[n - 1][1] = -1;

    for(int i = n - 2; ~i; --i)
        for(int j = i + 1; j < n; ++j) {
            mint c = get(i, j);
            if(i) {
                dp[i][0] += dp[j][1] * c;
                dp[i][1] += dp[j][0] * c;
            } else {
                dp[i][0] += dp[j][0] * c;
                dp[i][1] += dp[j][1] * c;
            }
        }

    cout << dp[0][0];
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
