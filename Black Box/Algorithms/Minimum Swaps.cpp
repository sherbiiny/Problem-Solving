// minimum adjacent swaps
// to convert a to b
int cost(vector<int> &a, vector<int> &b) {
    int n = a.size();
    map<int, deque<int>> pos;
    ordered_set<int> st;

    int res = 0;
    for (int i = 0; i < n; ++i) {
        pos[a[i]].push_back(i);
        st.insert(i);
    }

    for (int i = 0; i < n; ++i) {
        int idx = pos[b[i]].front();
        pos[b[i]].pop_front();
        res += st.order_of_key(idx);
        st.erase(idx);
    }

    return res;
}