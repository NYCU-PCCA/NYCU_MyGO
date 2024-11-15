struct zhu_liu { // O(VE)
  struct edge {
    int u, v;
    int w;
  };
  vector<edge> E; // 0-base
  int pe[MAXN], id[MAXN], vis[MAXN], in[MAXN];
  void init() { E.clear(); }
  void add_edge(int u, int v, int w) {
    if (u != v) E.eb(edge{u, v, w});
  }
  int build(int root, int n) {
    int ans = 0;
    for (;;) {
      fill_n(in, n, INF);
      for (int i = 0; i < SZ(E); ++i)
        if (E[i].u != E[i].v and E[i].w < in[E[i].v])
          pe[E[i].v] = i, in[E[i].v] = E[i].w;
      for (int u = 0; u < n; ++u) // no solution
        if (u != root and in[u] == INF) return -INF;
      int cntnode = 0;
      fill_n(id, n, -1), fill_n(vis, n, -1);
      for (int u = 0; u < n; ++u) {
        if (u != root) ans += in[u];
        int v = u;
        while (vis[v]!=u and id[v] == -1 and v != root)
          vis[v] = u, v = E[pe[v]].u;
        if (v != root and id[v] == -1) {
          for (int x = E[pe[v]].u; x != v;
               x = E[pe[x]].u)
            id[x] = cntnode;
          id[v] = cntnode++;
        }
      }
      if (!cntnode) break; // no cycle
      for (int u = 0; u < n; ++u)
        if (id[u] == -1) id[u] = cntnode++;
      for (int i = 0; i < SZ(E); ++i) {
        int v = E[i].v;
        E[i].u = id[E[i].u], E[i].v = id[E[i].v];
        if (E[i].u != E[i].v) E[i].w -= in[v];
      }
      n = cntnode, root = id[root];
    }
    return ans;
  }
};
