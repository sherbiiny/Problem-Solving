```typescript
function maxLengthBetweenEqualCharacters(s: string): number {
    let n = s.length, res = -1;
    for(let i = 0; i < n; ++i) {
        let curr = "";
        for(let j = i + 1; j < n; ++j) {
            if(s[j] == s[i])
                res = Math.max(res, curr.length);
            curr += s[j];
        }
    }

    return res;
};
```
