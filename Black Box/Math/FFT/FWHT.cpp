int add(int a, int b) {
  return (a + b) % mod;
}
 
int sub(int a, int b) {
  return (a - b + mod) % mod;
}
 
ll poww(ll a, ll b) {
  ll ret = 1;
  while (b) {
    if (b & 1) ret = ret * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ret;
}
 
void fwht(vector<int> &a, int inv, int f) {
  int sz = a.size();
  for (int len = 1; 2 * len <= sz; len <<= 1) {
    for (int i = 0; i < sz; i += 2 * len) {
      for (int j = 0; j < len; j++) {
        int x = a[i + j];
        int y = a[i + j + len];
 
        if (f == 0) {
          if (!inv)  a[i + j] = y, a[i + j + len] = add(x,  y);
          else  a[i + j] = sub(y, x), a[i + j + len] = x;
        }
        else if (f == 1) {
          if (!inv)  a[i + j + len] = add(x, y);
          else  a[i + j + len] = sub(y, x);
        }
        else {
          a[i + j] = add(x, y);
          a[i + j + len] = sub(x, y);
        }
      }   
    }
  }
}
 
vector<int> mul(vector<int> a, vector<int> b, int f) { // 0:AND, 1:OR, 2:XOR
  int sz = a.size();
  fwht(a, 0, f);  fwht(b, 0, f);
  vector<int> c(sz);
  for (int i = 0; i < sz; ++i) {
    c[i] = 1ll * a[i] * b[i] % mod;
  }
  fwht(c, 1, f);
  if (f) {
    int sz_inv = poww(sz, mod - 2);
    for (int i = 0; i < sz; ++i) {
      c[i] = 1ll * c[i] * sz_inv % mod;
    }
  }
  return c;
}