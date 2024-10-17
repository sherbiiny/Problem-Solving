```cpp
int minOperations(string s) {
  int ans = 0, n = s.size();

  for(int i = 1; i < n; ++i) {
      if(s[i] == s[i - 1]) {
          s[i] = s[i] == '0'? '1' : '0';
          ans++;
      }
  }

  return min(ans, n - ans);
}
```
