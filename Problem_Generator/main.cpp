#include "bits/stdc++.h"
#include "Random-generator/random_generator_lib.h"
using namespace std;
typedef long long ll;
#define endl '\n'
////////////////////////////////////////////////////////////

int idx = 11;
char x[] = "./tests/tst0000000.txt";

vector<int> pr, low;

void Sieve(int n) {
    low.assign(n + 1, 0);

    for (int i = 2; i <= n; ++i) {
        if (!low[i]) {
            low[i] = i;
            pr.push_back(i);
        }

        for (int &j: pr) {
            if (j > low[i] || i * j > n) break;
            low[j * i] = j;
        }
    }
}

// Function to calculate remainder for a large number string when divided by p
int getModulo(string num, int p) {
    int rem = 0;
    for(int i = 0; i < num.length(); i++)
        rem = (rem * 10 + (num[i] - '0')) % p;
    return rem;
}

// Find a number with k digits that when appended makes the entire number divisible by p
string findAppendNumber(const string& prefix, int k, int p) {
    string result(k, '0');
    int powerMod = 1;
    for(int i = 0; i < k; i++) {
        powerMod = ((ll)powerMod * 10) % p;
    }

    int prefixMod = getModulo(prefix, p);
    int target = (p - prefixMod * powerMod % p) % p;

    // Try all k-digit numbers until we find one that works
    for(int i = 0; i < p; i++) {
        string try_num = to_string(i);
        while(try_num.length() < k) try_num = "0" + try_num;
        if(getModulo(try_num, p) == target) {
            return try_num;
        }
    }
    return result;  // shouldn't reach here if p is not too large
}


void gen(int tc = 0) {
    if (x[idx] == '9') idx++;
    freopen(x, "w", stdout);
    x[idx]++;

    int p = pr[random32(1, pr.size() - 1)];
    int n = random32(1, 1e5 - 10);

    // Generate first n-3 digits randomly
    string num = "1";  // Start with 1 to ensure n digits
    for(int i = 1; i < n-3; i++) {
        num += (char)(random32(0, 9) + '0');
    }

    // Find the last 3 digits that make the entire number divisible by p
    string lastDigits = findAppendNumber(num, 3, p);
    num += lastDigits;

    cout << num << endl;
    cout << p + 1 << endl;
}

signed main() {
    Sieve(2e3);
    for(int tc = 0; tc < 10; ++tc)
        gen(tc);
}