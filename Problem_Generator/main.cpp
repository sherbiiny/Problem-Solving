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

    int t = random32(1, 2e5);
    cout << t << endl;
    int rem = 2e5;
    while(t--) {
      int n = random32(1, rem - t + 1);
      rem -= n;
      cout << n << endl;
      while(n--) cout << random32(1, 1e9) << ' ';
      cout << endl;
    }
}

signed main() {
    for(int tc = 0; tc < 15; ++tc)
        gen(tc);
}
