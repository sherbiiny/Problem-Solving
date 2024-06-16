// Get mod for big integer
int big_mod(string num, int a) {
    int res = 0;
    for (int i = 0; i < num.length(); i++) {
        res = (res * 10 + num[i] - '0') % a;
    }
    return res;
}