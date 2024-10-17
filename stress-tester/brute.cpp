#define _USE_MATH_DEFINES

/*
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
*/

#include <cmath>
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void fileIO(void) {

#ifndef ONLINE_JUDGE

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

#endif

}

void fastIO(void) {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

}

typedef long long ll;
#define int ll
typedef tree<int, null_type, greater_equal<int>, rb_tree_tag, tree_order_statistics_node_update> Ordered_Set; // find_by_order : element at index i
// order_of_key  : how many elements < A
// greater<int>
// less_equal<int>, greater_equal<int> : multiset


typedef unsigned long long ull;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<int, pi> p3i;

typedef pair<ll, ll> pll;
typedef pair<ll, pll> p3ll;

typedef pair<ll, ld> plld;
typedef pair<double, pi> pd2i;

typedef vector<int> vi;
typedef vector<pi> v2i;
typedef vector<p3i> v3i;

typedef vector<ll> vll;
typedef vector<pll> v2ll;
typedef vector<p3ll> v3ll;

typedef vector<string> vs;
typedef vector<bool> vb;

typedef vector<vi> vvi;
typedef vector<vll> vvl;

typedef priority_queue<int> pq_max;
typedef priority_queue<int, vi, greater<int>> pq_min;

#define loop(n)          for(int i = 0; i < (n); i++)
#define lp(x, s, e)      for(ll x = (s); x < (e); x++)
#define lpe(x, s, e)     for(ll x = (s); x <= (e); x++)

#define loop_r(n)          for(ll i = (n) - 1; i >= 0; i--)
#define lp_r(x, s, e)      for(ll x = (e) - 1; x >= (s); x--)
#define lpe_r(x, s, e)     for(ll x = (e); x >= (s); x--)

#define MP make_pair
#define PB push_back
#define EmB emplace_back
#define Em emplace
#define len(s)   (ll)s.length()
#define sz(v)    (ll)v.size()
#define all(a)   a.begin(),a.end()
#define all_r(a)   a.rbegin(),a.rend()
#define clr(x, val)    memset((x), (val), sizeof(x))
#define maxEle *max_element
#define minEle *min_element

#define tests ll t; cin >> t; ll i_t = 0; while(i_t++ < t)
#define SetPre(n, x)  cout << fixed << setprecision(n) << x

#define endl '\n'
#define kill return 0


#define ceil_i(a, b) (((ll)(a)+(ll)(b-1))/(ll)(b))
#define floor_i(a, b) (a/b)
#define round_i(a, b) ((a+(b/2))/b)

int dx_all[8] = {1, 0, -1, 0, 1, 1, -1, -1},
        dy_all[8] = {0, 1, 0, -1, -1, 1, -1, 1};

int dx[4] = {1, 0, -1, 0},
        dy[4] = {0, 1, 0, -1};


void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    sort(all(arr));


    int sum = 0;
    int idx = 0;
    int tot = 0;
    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i];
        if (sum == k) {
            sum -= arr[idx];
            arr.push_back(arr[idx++]);
            tot++;
            if (tot > n)
                return void(cout << -1 << endl);
        }
    }

    cout << 1 << endl;
}

signed main() {

    fastIO();
    cout << setprecision(10) << fixed;
    int t = 1;
    cin >> t;

    for (int i = 1; i <= t; ++i) {
        solve();

        /*cout << solve() << endl;*/

        /*if(solve())
            cout << "YES\n";
        else
            cout << "NO\n";*/

        /*cout << "Case #" << i << ": ";*/


        /*cout << "Case #" << i << ": " << (solve() ? "YES" : "NO") << endl;*/
    }

    kill;
}