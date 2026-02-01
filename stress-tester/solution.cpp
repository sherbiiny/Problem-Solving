#include <bits/stdc++.h>

using namespace std;
void fastIO(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

typedef long long ll;

const int oo = 1e9;
vector<int> to;
int n, f;
vector<vector<int>> has_patrol;

void dfs(int u, int t) {
    if(t > 2 * n) return;
    has_patrol[u][t] = 1;
    dfs(to[u], t + 1);
}

vector<vector<int>> dp;
int func(int u, int t) {
    if(has_patrol[u][t]) return -oo;
    if(t >= 2 * n) return 0;
    if(~dp[u][t])
        return dp[u][t];
    int ch1 = func(u, t + 1) + 1;
    int ch2 = func(to[u], t + 1);
    return dp[u][t] = max(ch1, ch2);
}

void solve(int tc) {

    cin >> n >> f;
    to.assign(n + 1, 0);
    has_patrol.assign(n + 1, vector<int>(2 * n + 1));
    for (int i = 1; i <= n; ++i) {
        cin >> to[i];
    }
    vector<int> patrol(f);
    for (int i = 0; i < f; ++i) {
        cin >> patrol[i];
        dfs(patrol[i], 0);
    }

    dp.assign(n + 1, vector<int>(2 * n + 1, -1));
    for (int i = 1; i <= n; ++i) {
        int ans = func(i, 0);
        if(ans <= -oo / 2) cout << -1 << '\n';
        else if(ans == 2 * n) cout << -2 << '\n';
        else cout << ans << '\n';
    }

}

signed main() {

    fastIO();
    cout << setprecision(10) << fixed;
    int t = 1; //cin >> t;

    for (int i = 1; i <= t; ++i)
        solve(i);

    return 0;
}