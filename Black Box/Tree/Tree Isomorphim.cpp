int n;
int treeID = 0;
vector<vector<int>> adj[2];
vector<int> sz[2], cent[2], name[2];
map<vector<int>, int> mp;

void getCent(int t, int u, int p) {
    sz[t][u] = 1;
    bool isCent = true;
    for(int &v: adj[t][u]){
        if(v == p) continue;
        getCent(t, v, u);
        sz[t][u] += sz[t][v];
        if(sz[t][v] > n / 2) isCent = false;
    }

    if(n - sz[t][u] > n / 2) isCent = false;
    if(isCent) cent[t].push_back(u);
}

void dfs(int t, int u, int p){
    vector<int> ch;
    for(int v : adj[t][u]){
        if(v == p) continue;
        dfs(t, v, u);
        ch.push_back(name[t][v]);
    }

    sort(ch.begin(), ch.end());
    if(!mp[ch]) mp[ch] = ++treeID;
    name[t][u] = mp[ch];
}

bool isIso() {
    // assign sizes first
    // you only need the dfs if the tree is rooted
    getCent(0, 1, 0);
    getCent(1, 1, 0);

    for(auto &a: cent[0])
        for(int &b: cent[1]) {
            dfs(0, a, 0), dfs(1, b, 0);
            if(name[0][a] == name[1][b]) return true;
        }

    return false;
}