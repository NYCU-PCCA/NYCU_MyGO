struct Matroid {
  Matroid(bitset<N>);  // init from an independent set
  bool can_add(int);   // check if break independence
  Matroid remove(int); // removing from the set
};
auto matroid_intersection(const vector<int> &w) {
  const int n = (int)w.size(); bitset<N> S;
  for (int sz = 1; sz <= n; sz++) {
    Matroid M1(S), M2(S); vector<vector<pii>> e(n + 2);
    for (int j = 0; j < n; j++) if (!S[j]) {
      if (M1.can_add(j)) e[n].eb(j, -w[j]);
      if (M2.can_add(j)) e[j].eb(n + 1, 0);
    }
    for (int i = 0; i < n; i++) if (S[i]) {
      Matroid T1 = M1.remove(i), T2 = M2.remove(i);
      for (int j = 0; j < n; j++) if (!S[j]) {
        if (T1.can_add(j)) e[i].eb(j, -w[j]);
        if (T2.can_add(j)) e[j].eb(i, w[i]);
      }
    } // maybe implicit build graph for more speed
    vector<pii> d(n + 2, {INF, 0}); d[n] = {0, 0};
    vector<int> prv(n + 2, -1);
    // change to SPFA for more speed, if necessary
    for (int upd = 1; upd--; )
      for (int u = 0; u < n + 2; u++)
        for (auto [v, c] : e[u]) {
          pii x(d[u].first + c, d[u].second + 1);
          if (x < d[v]) d[v] = x, prv[v] = u, upd = 1;
        }
    if (d[n + 1].first >= INF) break;
    for (int x = prv[n+1]; x!=n; x = prv[x]) S.flip(x);
    // S is the max-weighted independent set w/ size sz
  }
  return S;
} // from Nacl
