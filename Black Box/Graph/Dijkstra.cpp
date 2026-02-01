template<class T>
using minPQ = priority_queue<T, vector<T>, greater<>>;

vector<int> dijkstra(int src, int n) {
    vector<int> dist(n + 1, oo);
    minPQ<pair<int, int>> pq;
    dist[src] = 0;
    pq.emplace(0, src);

    while(!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();

        if(dist[u] < cost) continue;

        for(auto [v, w] : adj[u]) {
            if(dist[u] + w >= dist[v]) continue;
            dist[v] = dist[u] + w;
            pq.emplace(dist[v], v);
        }
    }

    return dist;
}