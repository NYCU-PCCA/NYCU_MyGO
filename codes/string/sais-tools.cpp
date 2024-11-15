template <int LG = 20> struct SparseTableSA : Suffix {
  array<vector<int>, LG> mn;
  SparseTableSA(const auto &s) : Suffix(s), mn{hi} {
    for (int l = 0; l + 1 < LG; l++) { mn[l+1].resize(n);
      for (int i = 0, len = 1 << l; i + len < n; i++)
        mn[l + 1][i] = min(mn[l][i], mn[l][i + len]);
    }
  }
  int lcp(int a, int b) {
    if (a == b) return n - a;
    a = rev[a] + 1, b = rev[b] + 1;
    if (a > b) swap(a, b);
    const int lg = __lg(b - a);
    return min(mn[lg][a], mn[lg][b - (1 << lg)]);
  } // equivalent to lca on the kruskal tree
  pair<int,int> get_range(int x, int len) { // WIP
    int a = rev[x] + 1, b = rev[x] + 1;
    for (int l = LG - 1; l >= 0; l--) {
      const int s = 1 << l;
      if (a + s <= n && mn[l][a] >= len) a += s;
      if (b - s >= 0 && mn[l][b - s] >= len) b -= s;
    }
    return {b - 1, a};
  } // if offline, solve get_range with DSU
};
