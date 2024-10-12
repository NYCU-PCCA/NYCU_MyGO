template <class Tp> void hessenberg_reduction(vector<vector<Tp>> &M) {
  // assert(M.size() == M[0].size());
  const int N = M.size();
  for (int r = 0; r < N - 2; r++) {
    int piv = -1;
    for (int h = r + 1; h < N; ++h) {
      if (M[h][r] != 0) {
        piv = h;
        break;
      }
    }
    if (piv < 0) continue;
    for (int i = 0; i < N; i++) swap(M[r + 1][i], M[piv][i]);
    for (int i = 0; i < N; i++) swap(M[i][r + 1], M[i][piv]);
    const auto rinv = Tp(1) / M[r + 1][r];
    for (int i = r + 2; i < N; i++) {
      const auto n = M[i][r] * rinv;
      for (int j = 0; j < N; j++) M[i][j] -= M[r + 1][j] * n;
      for (int j = 0; j < N; j++) M[j][r + 1] += M[j][i] * n;
    }
  }
}
template <class Tp> vector<Tp> characteristic_poly(vector<vector<Tp>> M) {
  hessenberg_reduction(M);
  const int N = M.size();
  vector<vector<Tp>> p(N + 1);
  p[0] = {1};
  for (int i = 0; i < N; i++) {
    p[i + 1].assign(i + 2, 0);
    for (int j = 0; j < i + 1; j++) p[i + 1][j + 1] += p[i][j];
    for (int j = 0; j < i + 1; j++) p[i + 1][j] -= p[i][j] * M[i][i];
    Tp betas = 1;
    for (int j = i - 1; j >= 0; j--) {
      betas *= M[j + 1][j];
      Tp hb = -M[j][i] * betas;
      for (int k = 0; k < j + 1; k++) p[i + 1][k] += hb * p[j][k];
    }
  }
  return p[N];
}
