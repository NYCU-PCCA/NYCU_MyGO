vector<pii> prufer(const vector<int> &code) {
  int n = SZ(code) + 2;
  vector<int> deg(n, 1);
  for (int i : code) ++deg[i];
  int ptr = 0;
  while (deg[ptr] != 1) ++ptr;
  int leaf = ptr;
  vector<pii> edges;
  for (int v : code) {
    edges.eb(leaf, v);
    if (--deg[v] == 1 and v < ptr) leaf = v;
    else { while (deg[++ptr] != 1); leaf = ptr; }
  }
  edges.eb(leaf, n-1);
  return edges;
}
