// Author: _Sherbiny

#include "bits/stdc++.h"
#include "Random-generator/random_generator_lib.h"
using namespace std;
typedef long long ll;
#define endl '\n'
void Hi() {
#ifndef ONLINE_JUDGE
freopen("in.in", "r", stdin);
freopen("o.in", "w", stdout);
#endif
ios_base::sync_with_stdio(false);
cin.tie(nullptr); cout.tie(nullptr);
}
////////////////////////////////////////////////////////////

int idx = 11;
char x[] = "./tests/tst0.txt";

void gen(int tc = 0) {

    if (x[idx] == '9')
        idx++;

    freopen(x, "w", stdout);
    x[idx]++;

    int n = random32(1, 100);
    int m = random32(n - 1, 100);
    int q = random32(1, 1000);

    cout << n << ' ' << m << endl;

    vector<pair<int, int>> tree = random_tree(n, 1);

    for(auto &[u, v] : tree) {
        int w = random32(1, 50);
        cout << u << ' ' << v << ' ' << w << endl;
    }

    m -= n - 1;
    while(m--) {
        int u = random32(1, n);
        int v = random32(1, n);
        int w = random32(1, 50);
        while(v == u)
            v = random32(1, n);
        cout << u << ' ' << v << ' ' << w << endl;
    }

    cout << q << endl;
    while(q--) {
        int u = random32(1, n);
        int v = random32(1, n);
        int w = random32(1, 50);
        while(v == u)
            v = random32(1, n);

        cout << u << ' ' << v << ' ' << w << endl;
    }
}

signed main() {
    for(int tc = 0; tc < 10; ++tc)
        gen(tc);
}
