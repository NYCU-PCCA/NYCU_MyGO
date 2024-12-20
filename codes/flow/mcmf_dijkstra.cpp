template<int MAXV, typename T = int,
  T INF = numeric_limits<T>::max()>
struct MCMF { // 0-base
  struct Edge {
    int from, to, rev;
    T cap, flow, cost;
  } *past[MAXV];
  vector<Edge> G[MAXV];
  bitset<MAXV> inq; int n, s, t;
  T dis[MAXV], up[MAXV], pot[MAXV];
  bool BellmanFord() {
    fill_n(dis, n, INF); inq.reset();
    queue<int> q;
    auto relax = [&](int u, T d, T cap, Edge *e) {
      if (cap > 0 and dis[u] > d) {
        dis[u] = d, up[u] = cap, past[u] = e;
        if (!inq[u]) inq[u] = 1, q.push(u);
      }
    };
    relax(s, 0, INF, 0);
    while (!q.empty()) {
      int u = q.front();
      q.pop(), inq[u] = 0;
      for (auto &e : G[u]) {
        T d2 = dis[u] + e.cost + pot[u] - pot[e.to];
        relax(e.to, d2, min(up[u], e.cap-e.flow), &e);
      }
    }
    return dis[t] != INF;
  }
  bool Dijkstra() {
    fill_n(dis, n, INF);
    MinHeap<pair<T,int>> pq;
    auto relax = [&](int u, T d, T cap, Edge *e) {
      if (cap > 0 and dis[u] > d) {
        dis[u] = d, up[u] = cap, past[u] = e;
        pq.ee(d, u);
      }
    };
    relax(s, 0, INF, 0);
    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (dis[u] != d) continue;
      for (auto &e : G[u]) {
        T d2 = dis[u] + e.cost + pot[u] - pot[e.to];
        relax(e.to, d2, min(up[u], e.cap-e.flow), &e);
      }
    }
    return dis[t] != INF;
  }
  auto solve(int _s, int _t, bool neg = true) {
    s = _s, t = _t; T flow = 0, cost = 0;
    if (neg) BellmanFord(), copy_n(dis, n, pot);
    for (; Dijkstra() /* BF */; copy_n(dis, n, pot)) {
      for (int i=0; i < n; ++i) dis[i]+=pot[i]-pot[s];
      flow += up[t], cost += up[t] * dis[t];
      for (int i = t; past[i]; i = past[i]->from) {
        auto &e = *past[i];
        e.flow += up[t], G[e.to][e.rev].flow -= up[t];
      }
    }
    return pair{ flow, cost };
  }
  void init(int _n) {
    n = _n, fill_n(pot, n, 0);
    for (int i = 0; i < n; ++i) G[i].clear();
  }
  void add_edge(int a, int b, T cap, T c) {
    G[a].eb(Edge{ a, b, SZ(G[b]), cap, 0,  c });
    G[b].eb(Edge{ b, a, SZ(G[a])-1, 0, 0, -c });
  }
};
