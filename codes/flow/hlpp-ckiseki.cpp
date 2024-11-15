template <typename T> struct HLPP {
  struct Edge { int to, rev; T flow, cap; };
  int n, mx; vector<vector<Edge>> adj;vector<T> excess;
  vector<int> d, cnt, active; vector<vector<int>> B;
  void add_edge(int u, int v, int f) {
    Edge a{v, (int)size(adj[v]), 0, f};
    Edge b{u, (int)size(adj[u]), 0, 0};
    adj[u].push_back(a), adj[v].push_back(b);
  }
  void enqueue(int v) {
    if (!active[v] && excess[v] > 0 && d[v] < n) {
      mx = max(mx, d[v]);
      B[d[v]].push_back(v); active[v] = 1;
    }
  }
  void push(int v, Edge &e) {
    T df = min(excess[v], e.cap - e.flow);
    if (df <= 0 || d[v] != d[e.to] + 1) return;
    e.flow += df, adj[e.to][e.rev].flow -= df;
    excess[e.to] += df, excess[v] -= df;
    enqueue(e.to);
  }
  void gap(int k) {
    for (int v = 0; v < n; v++) if (d[v] >= k)
      cnt[d[v]]--, d[v] = n, cnt[d[v]]++;
  }
  void relabel(int v) {
    cnt[d[v]]--; d[v] = n;
    for (auto e : adj[v])
      if (e.cap > e.flow) d[v] = min(d[v], d[e.to] +1);
    cnt[d[v]]++; enqueue(v);
  }
  void discharge(int v) {
    for (auto &e : adj[v])
      if (excess[v] > 0) push(v, e);
      else break;
    if (excess[v] <= 0) return;
    if (cnt[d[v]] == 1) gap(d[v]);
    else relabel(v);
  }
  T max_flow(int s, int t) {
    for (auto &e : adj[s]) excess[s] += e.cap;
    cnt[0] = n; enqueue(s); active[t] = 1;
    for (mx = 0; mx >= 0;)
      if (!B[mx].empty()) {
        int v = B[mx].back(); B[mx].pb();
        active[v] = 0; discharge(v);
      } else --mx;
    return excess[t];
  }
  HLPP(int _n) : n(_n), adj(n), excess(n),
    d(n), cnt(n + 1), active(n), B(n) {}
};
