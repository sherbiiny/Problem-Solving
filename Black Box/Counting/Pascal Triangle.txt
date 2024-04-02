vector<vector<ll>> PascalTriangle(ll n) {
    vector<vector<ll>> tri(n + 1);
    tri[0] = {1};

    for(int row = 1; row <= n; ++row) {
        tri[row].resize(row + 1);
        tri[row][0] = 1;
        for(int i = 0; i <= row / 2; ++i) {
            int curr = tri[row - 1][i];
            if(i)
                curr += tri[row - 1][i - 1];

            tri[row][i] = tri[row][row - i] = curr % mod;
        }
    }

    return tri;
}