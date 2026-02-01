// sum of numbers divisible by d in range
int calc(int l, int r, int d) {
  --l;
  ll sum = 1ll * d * (r / d) * (r / d + 1) / 2LL;
  sum -= 1ll * d * (l / d) * (l / d + 1) / 2LL;
  return sum;
}

// count number of y such that y%n = x (0 -> l)
int f(int l, int n, int x) {
 int cnt = (l / n) + (l % n >= x);
 return cnt;
}

