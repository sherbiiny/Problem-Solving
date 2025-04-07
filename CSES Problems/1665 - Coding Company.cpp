// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1665

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

mint dp[2][52][15001];

void magic() {
    int n, x; cin >> n >> x;
    vector<int> v(n);
    for(int &i: v) cin >> i;
    sort(v.begin(), v.end());

    int sum = accumulate(v.begin(), v.end(), 0);
    for (int r = 0; r <= x + sum; ++r)
        dp[n & 1][0][r] = 1;

    // i can be a start of a tream or an end of a tream
    // i also can be in a team that's already started
    // keep track of the remaining penalty
    // you have to end with 0 teams opened
    
    for(int i = n - 1; ~i; --i) {
        int it = i & 1;

        for(int r = 0; r <= x + sum; ++r)
            for(int cnt = 0; cnt <= n / 2; ++cnt) {
                // opening
                dp[it][cnt][r] = dp[it ^ 1][cnt + 1][r + v[i]];

                // closing
                if(cnt && v[i] <= r)
                    dp[it][cnt][r] += dp[it ^ 1][cnt - 1][r - v[i]] * cnt;

                // in between + opening and closing
                dp[it][cnt][r] += dp[it ^ 1][cnt][r] * (cnt + 1);
            }
    }

    cout << dp[0][0][x];
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
