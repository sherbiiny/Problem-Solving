// Author: _Sherbiny
// Problem Link: https://cses.fi/problemset/task/2205/

#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define endl '\n'
#define int ll
//====================//

/*

this problem can be solved recursively

if n = 1, the answer is {0, 1}
this is the base case

then for each n, we can generate the answer for n-1
let call it a

let b be a reversed copy of a

append 0 to each element in a
append 1 to each element in b

then concatenate a and b

this will give us the answer for n

*/

vector<int> go(int n) {
    if(n == 1) return {0, 1};
    auto a = go(n - 1);
    auto b = a;
    reverse(b.begin(), b.end());
    for(int &i: a) i *= 2;
    for(int &i: b) a.push_back(i * 2 + 1);
    return a;
}

void magic() {
    int n; cin >> n;
    for(int x: go(n))
        cout << bitset<16>(x).to_string().substr(16 - n) << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    int t = 1;
    while (t--) magic();
}
