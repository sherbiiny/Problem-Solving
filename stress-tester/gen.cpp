#include "bits/stdc++.h"
using namespace std;
using ll = long long;
#define endl '\n'
#define int ll
//====================//

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define get(l, r) uniform_int_distribution<long long>(l, r)(rng)

void magic() {
    // 1. Generate N and F
    // Constraints: 2 <= N <= 2000, 1 <= F <= N
    int n = get(2, 2000);
    int f = get(1, n);

    cout << n << ' ' << f << endl;

    // 2. Generate functional graph (a[i] != i)
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int to;
        do {
            to = get(1, n);
        } while (to == i);
        a[i] = to;
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << ' ';
        cout << a[i];
    }
    cout << endl;

    // 3. Generate unique patrol starting stations
    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 1);
    shuffle(nodes.begin(), nodes.end(), rng);

    for (int i = 0; i < f; i++) {
        if (i) cout << ' ';
        cout << nodes[i];
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    magic();
}
