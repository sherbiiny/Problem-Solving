const int N = 3001, oo = 2e18;
int dp[N][2], it = 1, L = 1, R = 0, sum = 0;
int a[N];

void add(int i) {
    //
}

void rem(int i) {
    //
}

void move(int l, int r) {
    while(R < r) add(++R);
    while(L > l) add(--L);
    while(R > r) rem(R--);
    while(L < l) rem(L++);
}

void go(int l, int r, int lx, int rx) {
    if(l > r) return;

    int m = (l + r) / 2, opt = 1;
    for(int i = lx; i <= min(rx, m); ++i) {
        move(i, m);
        int curr = dp[i - 1][it ^ 1] + sum;
        if(curr > dp[m][it])
            dp[m][it] = curr, opt = i;
    }

    go(l, m - 1, lx, opt);
    go(m + 1, r, opt, rx);
}

void magic() {
    int n, k; cin >> n >> k;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    // base case
    memset(dp, 0, sizeof dp);
    it = 1;

    // calculate
    for(int i = 1; i <= k; ++i, it ^= 1)
        go(1, n, 1, n);


    cout << dp[n][k & 1];
}