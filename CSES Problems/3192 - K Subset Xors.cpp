// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/3192

#include "bits/stdc++.h"
using namespace std;
 
typedef long long ll;
#define endl '\n'
#define int ll
//====================//
 
struct Basis {
    int B, sz = 0;
    vector<int> b;
 
    Basis(int B): B(B), b(B) {}
 
    void insert(int x) {
        for(int i = B - 1; ~i; --i) {
            if(!(x >> i & 1)) continue;
            if(!b[i]) {
                b[i] = x, ++sz;
                return;
            }
            x ^= b[i];
        }
    }
 
    bool can(int x) {
        for(int i = B - 1; ~i; --i) {
            if(!(x >> i & 1)) continue;
            if(!b[i]) return 0;
            x ^= b[i];
        }
        return !x;
    }
 
    int mx() {
        int x = 0;
        for(int i = B - 1; ~i; --i) x = max(x, x ^ b[i]);
        return x;
    }
 
    int kth(int k) {
        int x = 0, cnt = 1ll << sz;
        for(int i = B - 1; ~i; --i) {
            if(!b[i]) continue;
            cnt /= 2;
            if(x >> i & 1) {
                if(cnt >= k) x ^= b[i];
                else k -= cnt;
            }
            else if(cnt < k) x ^= b[i], k -= cnt;
        }
        return x;
    }
};
 
int k;
 
int mul(int a, int b) {
    if(a > k / b) return k + 1;
    return a * b;
}
 
int power(int a, int b) {
    int res = 1;
    while(b) {
        if(b&1) res = mul(res, a);
        a = mul(a, a), b >>= 1;
    }
    return res;
}
 
void magic() {
    int n; cin >> n >> k;
    Basis b(32);
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        b.insert(x);
    }
 
    int cnt = power(2, n - b.sz);
 
    int rem = k;
    for(int i = 1; i <= k; ++i) {
        int c = cnt, me = b.kth(i);
        while(rem > 0 && c > 0) {
            --rem, --c;
            cout << me << ' ';
        }
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}