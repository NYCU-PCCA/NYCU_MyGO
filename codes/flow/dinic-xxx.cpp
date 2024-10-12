template <typename Cap = int>
struct Dinic { // 0-base
  struct Edge { int to, rev; Cap cap, fl; };
  const Cap INF = numeric_limits<Cap>::max() >> 1;
  vector<vector<Edge>> G;
  vector<int> dis, cur;
  int s, t, n;
  Cap dfs(int u, Cap cap) {
    if (u == t or !cap) return cap;
    for (int &i = cur[u]; i < SZ(G[u]); ++i) {
      Edge &e = G[u][i];
      if (dis[e.to] == dis[u] + 1 and e.fl != e.cap) {
        Cap df = dfs(e.to, min(e.cap - e.fl, cap));
        if (df) {
          e.fl += df;
          G[e.to][e.rev].fl -= df;
          return df;
        }
      }
    }
    dis[u] = -1;
    return 0;
  }
  bool bfs() {
    fill(ALL(dis), -1);
    queue<int> q;
    q.push(s), dis[s] = 0;
    while (!q.empty()) {
      int tmp = q.front(); q.pop();
      for (Edge &e : G[tmp])
        if (!~dis[e.to] and e.fl != e.cap)
          dis[e.to] = dis[tmp] + 1, q.push(e.to);
    }
    return dis[t] != -1;
  }
  Cap maxflow(int _s, int _t) {
    s = _s, t = _t;
    Cap flow = 0, df;
    while (bfs()) {
      fill(ALL(cur), 0);
      while ((df = dfs(s, INF))) flow += df;
    }
    return flow;
  }
  void init(int _n) {
    n = _n;
    G.assign(n, vector<Edge>());
    dis.resize(n), cur.resize(n);
  }
  void reset() {
    for (int i = 0; i < n; ++i)
      for (Edge &e : G[i]) e.fl = 0;
  }
  void add_edge(int u, int v, int cap) {
    G[u].eb(v, SZ(G[v]), cap, 0);
    G[v].eb(u, SZ(G[u]) - 1, 0, 0);
  }
};