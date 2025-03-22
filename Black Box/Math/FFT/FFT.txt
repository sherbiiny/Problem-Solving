using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1){
        cd omg = exp(cd(0, 2.0 * PI / len * (invert ? -1 : 1)));
        for(int i = 0; i < n; i += len) {
            auto curOmg = cd(1, 0);
            for(int j = 0; j < len/2; ++j) {
                cd e = a[i + j], o = a[i + j + len/2] * curOmg;
                a[i + j] = e + o;
                a[i + j + len/2] = e - o;
                curOmg *= omg;
            }
        }
    }
}

vector<int> multiply(vector<int> & a, vector<int> & b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa, false), fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real() / n);
    return result;
}

vector<int> power(vector<int> &a, int b) {
    vector<int> res{1};
    while (b) {
        if (b & 1) res = multiply(res, a);
        a = multiply(a, a), b >>= 1;
    }
    return res;
}