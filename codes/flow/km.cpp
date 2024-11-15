struct KM { // maximize, test @ UOJ 80
  int n, l, r; lld ans; // fl and fr are the match
  vector<lld> hl, hr; vector<int> fl, fr, pre, q;
  void bfs(const auto &w, int s) {
    vector<int> vl(n), vr(n); vector<lld> slk(n, INF);
    l = r = 0; vr[q[r++] = s] = true;
    auto check = [&](int x) -> bool {
      if (vl[x] || slk[x] > 0) return true;
      vl[x] = true; slk[x] = INF;
      if (fl[x] != -1) return (vr[q[r++] = fl[x]] = true);
      while (x != -1) swap(x, fr[fl[x] = pre[x]]);
      return false;
    };
    while (true) {
      while (l < r)
        for (int x = 0, y = q[l++]; x < n; ++x) if (!vl[x])
          if (chmin(slk[x], hl[x] + hr[y] - w[x][y]))
            if (pre[x] = y, !check(x)) return;
      lld d = ranges::min(slk);
      for (int x = 0; x < n; ++x)
        vl[x] ? hl[x] += d : slk[x] -= d;
      for (int x = 0; x < n; ++x) if (vr[x]) hr[x] -= d;
      for (int x = 0; x < n; ++x) if (!check(x)) return;
    }
  }
  KM(int n_, const auto &w) : n(n_), ans(0),
    hl(n), hr(n), fl(n, -1), fr(fl), pre(n), q(n) {
    for (int i = 0; i < n; ++i) hl[i]=ranges::max(w[i]);
    for (int i = 0; i < n; ++i) bfs(w, i);
    for (int i = 0; i < n; ++i) ans += w[i][fl[i]];
  }
}; // find maximum perfect matching
// To obtain the max match of exactly K edges for
// K = 1 ... N, initialize hl[i] = INF and bfs from all
// unmatched right part point (fr[i] == -1)
