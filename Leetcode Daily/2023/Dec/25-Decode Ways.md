```typescript
function numDecodings(s: string): number {
    let n = s.length;

    let doubleDigit = (i: number): number => {
        if(i == n - 1)
            return -1;
        let num = parseInt(s[i]) * 10 + parseInt(s[i + 1]);
        if(num <= 26)
            return num;
        return -1;
    }

    let dp = [];
    dp[n] = 1;
    for(let i = n - 1; i >= 0; --i) {
        if(s[i] == '0') {
            dp[i] = 0;
            continue
        }
        dp[i] = dp[i + 1];
        let two = doubleDigit(i);
        if(~two)
            dp[i] += dp[i + 2];
    }

    return dp[0];
};
```
