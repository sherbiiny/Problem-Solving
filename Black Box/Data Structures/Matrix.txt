template<class T>
struct Matrix {
    int n, m;
    vector<vector<T>> a;

    Matrix(int _n, int _m) {
        n = _n, m = _m;
        a.assign(n, vector<T>(m));
    }

    Matrix operator *(const Matrix &b) {
        int r = n, c = b.m, k = m;
        Matrix res(r, c);
        for(int i = 0; i < r; ++i)
            for(int j = 0; j < c; ++j)
                for(int o = 0; o < k; ++o)
                    res.a[i][j] += a[i][o] * b.a[o][j];
        return res;
    }


    friend Matrix power(Matrix mat, ll p) {
        if(p == 0) {
            Matrix ones(mat.n, mat.n);
            for(int i = 0; i < mat.n; ++i)
                ones.a[i][i] = 1;
            return ones;
        }
        Matrix ret = power(mat * mat, p / 2);
        if(p&1) ret = ret * mat;
        return ret;
    }

    void display() {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) cout << a[i][j] << ' ';
            cout << endl;
        }
    }
};