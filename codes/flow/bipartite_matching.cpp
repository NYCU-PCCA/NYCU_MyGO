struct Bipartite_Matching { // 0-base
  int l, r;
  vector<int> mp, mq, dis, cur;
  vector<vector<int>> G;
  bool dfs(int u) {
    for (int &i = cur[u]; i < SZ(G[u]); ++i) {
      int e = G[u][i];
      if (mq[e] == l or (dis[mq[e]] == dis[u] + 1 and dfs(mq[e])))
        return mp[mq[e] = u] = e, 1;
    }
    return dis[u] = -1, 0;
  }
  bool bfs() {
    queue<int> q;
    fill(ALL(dis), -1);
    for (int i = 0; i < l; ++i)
      if (!~mp[i]) dis[i] = 0, q.push(i);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int e : G[u]) if (!~dis[mq[e]]) {
        dis[mq[e]] = dis[u] + 1, q.push(mq[e]);
      }
    }
    return dis[l] != -1;
  }
  int matching() {
    int res = 0;
    fill(ALL(mp), -1), fill(ALL(mq), l);
    while (bfs()) {
      fill(ALL(cur), 0);
      for (int i = 0; i < l; ++i)
        res += (!~mp[i] and dfs(i));
    }
    return res; // (i, mp[i] != -1)
  }
  void add_edge(int s, int t) { G[s].eb(t); }
  void init(int _l, int _r) {
    l = _l, r = _r;
    mp.resize(l), mq.resize(r);
    dis.resize(l+1), cur.resize(l);
    G.assign(l+1, vector<int>());
  }
};
