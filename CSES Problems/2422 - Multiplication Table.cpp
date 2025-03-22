// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/2422

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//
 
void magic() {
    int n; cin >> n;
 
    // make sure you search for the first true not the other way around
    // this will guarantee that the answer is in the grid
    int l = 1, r = n * n, mid, ans = n;
    while(l <= r) {
        mid = l + (r - l) / 2;
 
        int sum = 0;
        for(int i = 1; i <= n; ++i) {
            sum += min(n, mid / i);
            if(sum > (n * n + 1) / 2) break;
        }
 
        if(sum >= (n * n + 1) / 2) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
 
    cout << ans << endl;
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}