template <typename Cap = int64_t> struct Dinic {
  struct E { int to, rev; Cap cap; }; int n, st, ed;
  vector<vector<E>> G; vector<size_t> lv, idx;
  bool BFS(int k) {
    lv.assign(n, 0); idx.assign(n, 0);
    queue<int> bfs; bfs.push(st); lv[st] = 1;
    while (not bfs.empty() and not lv[ed]) {
      int u = bfs.front(); bfs.pop();
      for (auto e: G[u]) if (e.cap >> k and !lv[e.to])
        bfs.push(e.to), lv[e.to] = lv[u] + 1;
    }
    return lv[ed];
  }
  Cap DFS(int u, Cap f = numeric_limits<Cap>::max()) {
    if (u == ed) return f;
    Cap ret = 0;
    for (auto &i = idx[u]; i < G[u].size(); ++i) {
      auto &[to, rev, cap] = G[u][i];
      if (cap <= 0 or lv[to] != lv[u] + 1) continue;
      Cap nf = DFS(to, min(f, cap));
      ret += nf; cap -= nf; f -= nf;
      G[to][rev].cap += nf;
      if (f == 0) return ret;
    }
    if (ret == 0) lv[u] = 0;
    return ret;
  }
  void init(int n_) { G.assign(n = n_, vector<E>()); }
  void add_edge(int u, int v, Cap c) {
    G[u].eb(v, int(G[v].size()), c);
    G[v].eb(u, int(G[u].size())-1, 0);
  }
  Cap max_flow(int st_, int ed_) {
    st = st_, ed = ed_; Cap ret = 0;
    for (int i = 63; i >= 0; --i)
      while (BFS(i)) ret += DFS(st);
    return ret;
  }
}; // test @ luogu P3376
