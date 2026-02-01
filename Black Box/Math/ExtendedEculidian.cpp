// ax + by = gcd -> x = x. + b / gcd * T, y = y. - a / gcd * T
int extendedEuclidean(int a, int b, int &x, int &y) {
    if (not b) {
        x = 1, y = 0;
        return a;
    }

    long long i, j;
    long long g = extendedEuclidean(b, a % b, i, j);
    x = j, y = i - a / b * j;
    return g;
}