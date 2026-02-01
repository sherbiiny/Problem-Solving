mint fact[N], invr[N];
void build() {
    fact[0] = 1;
    for(int i = 1; i < N; ++i) fact[i]=fact[i-1]*i;
    invr[N - 1] = inv(fact[N - 1]);
    for(int i = N - 2; ~i; --i) invr[i] = invr[i + 1] * (i + 1);
}

mint nPr(int n, int r) {return n<r?0:fact[n]*invr[n - r];}
mint nCr(int n, int r) {return nPr(n, r)*invr[r];}
mint SAndBars(int n, int k) {return min(n, k)<0?0:nCr(n+k-1, k-1);}
mint catalan(int n) {return nCr(n * 2, n) / (n + 1);}


// for small r
int nCr(int n, int r){ 
    __int128 sum = 1; 
    for (int i = 1; i <= r; i++) sum = sum * (n - r + i) / i; 
    return (int)sum; 
}

// nCr parity
int nCr(int n, int r){
    if(n < r) return 0;
    return (n & r) == r;
}

// pascal triangle
const int N = 1001;
int nCr[N][N];

void PascalTriangle(ll n) {
    nCr[0][0] = 1;

    for(int row = 1; row <= n; ++row) {
        nCr[row][0] = 1;
        for(int i = 0; i <= row / 2; ++i) {
            int curr = nCr[row - 1][i];
            if(i) curr += nCr[row - 1][i - 1];

            nCr[row][i] = nCr[row][row - i] = curr % mod;
        }
    }
}
