struct Cent_Dec { // 1-base
  vector<pii> G[MAXN];
  pii info[MAXN], upinfo[MAXN]; // itself / climbing up
  int n, pa[MAXN], layer[MAXN], sz[MAXN], done[MAXN];
  int dis[__lg(MAXN) + 1][MAXN];
  void init(int _n) {
    n = _n, layer[0] = -1;
    fill_n(pa + 1, n, 0), fill_n(done + 1, n, 0);
    for (int i = 1; i <= n; ++i) G[i].clear();
  }
  void add_edge(int a, int b, int w) {
    G[a].eb(b, w), G[b].eb(a, w);
  }
  void get_cent(
    int x, int f, int &mx, int &c, int num) {
    int mxsz = 0;
    sz[x] = 1;
    for (auto [y,w] : G[x])
      if (!done[y] and y != f) {
        get_cent(y, x, mx, c, num);
        sz[x] += sz[y], mxsz = max(mxsz, sz[y]);
      }
    if (mx > max(mxsz, num - sz[x]))
      mx = max(mxsz, num - sz[x]), c = x;
    if (chmin(mx, max(mxsz, num - sz[x]))) c = x;
  }
  void dfs(int x, int f, int d, int org) {
    // if required, add self info or climbing info
    dis[layer[org]][x] = d;
    for (auto [y,w] : G[x])
      if (!done[y] && y != f)
        dfs(y, x, d + w, org);
  }
  int cut(int x, int f, int num) {
    int mx = 1e9, c = 0, lc;
    get_cent(x, f, mx, c, num);
    done[c] = 1, pa[c] = f, layer[c] = layer[f] + 1;
    for (auto [y,w] : G[c])
      if (!done[y]) {
        if (sz[y] > sz[c])
          lc = cut(y, c, num - sz[c]);
        else lc = cut(y, c, sz[y]);
        upinfo[lc] = pii(), dfs(y, c, w, c);
      }
    return done[c] = 0, c;
  }
  void build() { cut(1, 0, n); }
  void modify(int x) {
    for (int a = x, ly = layer[a]; a;
         a = pa[a], --ly) {
      info[a].X += dis[ly][x], ++info[a].Y;
      if (pa[a])
        upinfo[a].X += dis[ly - 1][x], ++upinfo[a].Y;
    }
  }
  int query(int x) {
    int rt = 0;
    for (int a = x, ly = layer[a]; a;
         a = pa[a], --ly) {
      rt += info[a].X + info[a].Y * dis[ly][x];
      if (pa[a])
        rt -=
          upinfo[a].X + upinfo[a].Y * dis[ly - 1][x];
    }
    return rt;
  }
};
