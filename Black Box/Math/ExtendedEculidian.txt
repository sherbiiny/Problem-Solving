long long extendedEuclidean(long long a, long long b, long long &x, long long &y) {
    if (not b) {
        x = 1, y = 0;
        return a;
    }

    long long i, j;
    long long g = extendedEuclidean(b, a % b, i, j);
    x = j, y = i - a / b * j;
    return g;
}
// ax + by = gcd -> x = x. + b / gcd * T, y = y. - a / gcd * T