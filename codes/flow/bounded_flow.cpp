struct Dinic /* BoundedFlow */ { // 0-base, MAXM, INF
  struct edge { int to, cap, flow, rev; };
  vector<edge> G[MAXM];
  int n, s, t, dis[MAXM], cur[MAXM], cnt[MAXM];
  void init(int _n) {
    n = _n;
    for (int i = 0; i < n + 2; ++i)
      G[i].clear(), cnt[i] = 0;
  }
/*void add_edge(int u, int v, int lcap, int rcap) {
    cnt[u] -= lcap, cnt[v] += lcap;
    G[u].eb(edge{v, rcap, lcap, SZ(G[v])});
    G[v].eb(edge{u, 0, 0, SZ(G[u]) - 1});
  } */
  void add_edge(int u, int v, int cap) {
    G[u].eb(edge{ v, cap, 0, SZ(G[v]) });
    G[v].eb(edge{ u, 0, 0, SZ(G[u]) - 1 });
  }
  int dfs(int u, int cap) {
    if (u == t or !cap) return cap;
    for (int &i = cur[u]; i < SZ(G[u]); ++i) {
      edge &e = G[u][i];
      if (dis[e.to] == dis[u] + 1 and e.cap != e.flow) {
        int df = dfs(e.to, min(e.cap - e.flow, cap));
        if (df) {
          e.flow += df, G[e.to][e.rev].flow -= df;
          return df;
        }
      }
    }
    dis[u] = -1;
    return 0;
  }
  bool bfs() {
    fill_n(dis, n + 3, -1);
    queue<int> q; q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (edge &e : G[u])
        if (dis[e.to] == -1 and e.flow != e.cap)
          q.push(e.to), dis[e.to] = dis[u] + 1;
    }
    return dis[t] != -1;
  }
  int maxflow(int _s, int _t) {
    s = _s, t = _t;
    int flow = 0, df;
    while (bfs()) {
      fill_n(cur, n + 3, 0);
      while ((df = dfs(s, INF))) flow += df;
    }
    return flow;
  }
/*bool solve() {
    int sum = 0;
    for (int i = 0; i < n; ++i)
      if (cnt[i] > 0)
        add_edge(n + 1, i, cnt[i]), sum += cnt[i];
      else if (cnt[i] < 0) add_edge(i, n + 2, -cnt[i]);
    if (sum != maxflow(n + 1, n + 2)) sum = -1;
    for (int i = 0; i < n; ++i)
      if (cnt[i] > 0)
        G[n + 1].pb(), G[i].pb();
      else if (cnt[i] < 0)
        G[i].pb(), G[n + 2].pb();
    return sum != -1;
  }
  int solve(int _s, int _t) {
    add_edge(_t, _s, INF);
    if (!solve()) return -1; // invalid flow
    int x = G[_t].back().flow;
    return G[_t].pb(), G[_s].pb(), x;
  } */
};
