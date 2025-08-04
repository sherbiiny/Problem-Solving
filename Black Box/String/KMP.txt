vector<int> PI(string& s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; ++i, j = pi[i - 1]) {
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) pi[i] = j + 1;
    }
    return pi;
}

auto computeAutometa(string &s) {
    s += '#';
    int n = s.size();
    vector<int> pi = PI(s);

    auto nxt = vector(n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i]) nxt[i][c] = nxt[pi[i-1]][c];
            else nxt[i][c] = i + ('a' + c == s[i]);
        }
    }

    return nxt;
}