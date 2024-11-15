Dinic dinic;
int g[MAXN];
void GomoryHu(int n) { // 0-base
  fill_n(g, n, 0);
  for (int i = 1; i < n; ++i) {
    dinic.reset();
    add_edge(i, g[i], dinic.maxflow(i, g[i]));
    for (int j = i + 1; j <= n; ++j)
      if (g[j] == g[i] && ~dinic.dis[j])
        g[j] = i;
  }
}
