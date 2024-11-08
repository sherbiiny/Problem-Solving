// Author: _Sherbiny

#include "bits/stdc++.h"
using namespace std;

#ifdef DBG
#include "./debug.h"
#else
#define dbg(...)
#endif

typedef long long ll;
#define endl '\n'
#define int ll
//==================//

const ll oo = -2e18;

struct twoStackQueue {
    stack<pair<ll, ll>> a, b;

    int size() {
        return a.size() + b.size();
    }

    void push(ll val) {
        ll mx = a.empty()? oo : a.top().second;
        a.push({val, max(mx, val)});
    }

    void move() {
        ll mx = oo;
        while(!a.empty()) {
            mx = max(a.top().first, mx);
            b.push({a.top().first, mx});
            a.pop();
        }
    }

    ll getMax() {
        ll mx = oo;

        if(!b.empty())
            mx = max(mx, b.top().second);
        if(!a.empty())
            mx = max(mx, a.top().second);

        return mx;
    }

    void pop() {
        if(b.empty())
            move();
        if(!b.empty())
            b.pop();
    }
};

void magic() {
    int n, m, d; cin >> n >> m >> d;
    vector<array<int, 3>> v(m);
    for(auto &[t, a, b]: v)
        cin >> a >> b >> t;

    sort(v.begin(), v.end());

    vector<int> dp(n + 2), newDp(n + 2);

    twoStackQueue q;

    for(int x = 1; x <= n; ++x)
        dp[x] = v[m - 1][2] - abs(x - v[m - 1][1]);

    for(int i = m - 2; i >= 0; --i) {
        int timeDiff = v[i + 1][0] - v[i][0];

        for(int x = 1; x <= min(n, d * timeDiff); ++x)
            q.push(dp[x]);

        for(int x = 1; x <= n; ++x) {
            if(x + d * timeDiff <= n)
                q.push(dp[x + d * timeDiff]);
            if(q.size() > timeDiff * 2 * d + 1)
                q.pop();

            // r --> x + d * td
            // l --> x - d * td
            // sz <= 2 * d * td + 1


            int gain = v[i][2] - abs(x - v[i][1]);
            newDp[x] = q.getMax() + gain;
        }

        while(q.size()) q.pop();

        swap(dp, newDp);
    }

    int res = oo;
    for(int x = 1; x <= n; ++x)
        res = max(res, dp[x]);

    cout << res << endl;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) magic();
}
