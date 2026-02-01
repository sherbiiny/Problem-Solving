vector<int> pr, low;
void Sieve(int n) {
    low.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (!low[i]) pr.push_back(low[i] = i);
        for (int &j: pr) {
            if (j > low[i] || i * j > n) break;
            low[j * i] = j;
        }
    }
}