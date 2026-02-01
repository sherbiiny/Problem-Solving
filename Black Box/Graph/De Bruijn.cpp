string A = "01"; // Character set
unordered_set<string> seen;
vector<int> edges;

void dfs(string node) {
    for (int i = 0; i < A.size(); ++i) {
        string str = node + A[i];
        if (!seen.count(str)) {
            seen.insert(str);
            dfs(str.substr(1));
            edges.push_back(i);
        }
    }
}

string deBruijn(int n) {
    seen.clear(), edges.clear();
    auto st = string(n - 1, A[0]);
    dfs(st);

    string res;
    int l = pow(A.size(), n);
    for (int i = 0; i < l; ++i) res += A[edges[i]];
    res += st;

    return res;
}