vector<array<int, 2>> mergeSegments(vector<array<int, 2>> v) {
    if (v.empty()) return v;
    sort(v.begin(), v.end());
    vector<array<int, 2>> res;
    
    auto [l, r] = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i][0] <= r) r = max(r, v[i][1]);
        else {
            res.push_back({l, r});
            l = v[i][0], r = v[i][1];
        }
    }
    
    res.push_back({l, r});
    return res;
}