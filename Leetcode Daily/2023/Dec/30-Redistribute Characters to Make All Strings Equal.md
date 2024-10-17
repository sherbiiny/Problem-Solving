```cpp
class Solution {
public:
    bool makeEqual(vector<string>& words) {
        int f[26] = {0};
        for(string s : words)
            for(char c : s)
                f[c - 'a']++;

        int n = words.size();
        for(int i = 0; i < 26; ++i)
            if(f[i] % n)
                return false;
        return true;
    }
};
```
