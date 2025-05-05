// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/2115

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1){
        cd omg = exp(cd(0, 2.0 * PI / len * (invert ? -1 : 1)));
        for(int i = 0; i < n; i += len) {
            auto curOmg = cd(1, 0);
            for(int j = 0; j < len/2; ++j) {
                cd e = a[i + j], o = a[i + j + len/2] * curOmg;
                a[i + j] = e + o;
                a[i + j + len/2] = e - o;
                curOmg *= omg;
            }
        }
    }
}

vector<int> multiply(vector<int> & a, vector<int> & b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa, false), fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real() / n);
    return result;
}

void magic() {
    string s; cin >> s;
    int n = s.size();
    vector<int> a(n + 1), b(n + 1);

    int pref = 0;
    a[pref]++, b[n - pref]++;
    for(int i = 0; i < n; ++i) {
        pref += s[i] - '0';
        a[pref]++, b[n - pref]++;
    }

    a = multiply(a, b);

    int tot = 0, cnt = 0;
    for(int i = 0; i < n; ++i) {
        if(s[i] == '0') ++cnt, tot += cnt;
        else cnt = 0;
    }

    cout << tot << ' ';
    for(int k = 1; k <= n; ++k)
        cout << a[k + n] << ' ';
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
