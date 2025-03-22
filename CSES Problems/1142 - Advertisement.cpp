// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/1142

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//
 
vector<int> nextSmaller(vector<int> &v) {
    int n = v.size();
    vector<int> res(n, n);
    vector<int> st;
    for (int i = 0; i < n; ++i) {
        if (st.empty() || v[i] >= v[st.back()]) st.push_back(i);
        else {
            res[st.back()] = i;
            st.pop_back();
            --i;
        }
    }
    return res;
}
 
vector<int> prevSmaller(vector<int> &v) {
    int n = v.size();
    vector<int> res(n, -1);
    vector<int> st;
    for (int i = n - 1; i >= 0; --i) {
        // you may need to remove the equal
        if (st.empty() || v[i] >= v[st.back()]) st.push_back(i);
        else {
            res[st.back()] = i;
            st.pop_back();
            ++i;
        }
    }
    return res;
}
 
void magic() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &i: v) cin >> i;
 
    vector<int> nxt = nextSmaller(v);
    vector<int> prv = prevSmaller(v);
 
    int ans = 0;
    for(int i = 0; i < n; ++i)
        ans = max(ans, (nxt[i] - prv[i] - 1) * v[i]);
 
    cout << ans;
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}