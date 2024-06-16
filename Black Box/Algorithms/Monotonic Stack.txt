vector<int> nextGreater(vector<int> &v) {
    int n = v.size();
    vector<int> res(n, n);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        if (st.empty() || v[i] <= v[st.top()]) st.push(i);
        else {
            res[st.top()] = i;
            st.pop();
            --i;
        }
    }
    return res;
}
 
vector<int> prevGreater(vector<int> &v) {
    int n = v.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = n - 1; i >= 0; --i) {
        // you may need to remove the equal
        if (st.empty() || v[i] <= v[st.top()]) st.push(i);
        else {
            res[st.top()] = i;
            st.pop();
            ++i;
        }
    }
    return res;
}