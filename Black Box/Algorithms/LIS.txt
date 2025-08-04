vector<int> LIS(vector<int> &a) {
    int n = size(a);
    vector<int> L(n), res(n);
    int lisCount = 0;
    for (int i = 0; i < n; ++i) {
        // if you need equal values change it to upper_bound
        ll pos = lower_bound(L.begin(), L.begin() + lisCount, a[i]) - L.begin();
        L[pos] = a[i];
        if (pos == lisCount) ++lisCount;
        res[i] = pos + 1;
    }
    return res;
}