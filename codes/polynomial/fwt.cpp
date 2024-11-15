/* x: a[i+j], y: a[i+j+L/2]
or: (y += x * op), and: (x += y * op)
xor: (x, y = (x + y) * op, (x - y) * op)
invop: or, and, xor = -1, -1, 1/2 */
void fwt(int *a, int n, int op) { // or
  for (int L = 2; L <= n; L <<= 1)
    for (int i = 0; i < n; i += L)
      for (int j = 0; j < L/2; ++j)
        a[i+j+L/2] = (a[i+j+L/2] + a[i+j] * op) % mod;
}
constexpr int MAXN = 20 + 1, P2N = 1 << MAXN;
int f[MAXN][P2N], g[MAXN][P2N], h[MAXN][P2N], ct[P2N];
void subset_convolution(int *a, int *b, int *c, int L) {
  // c_k = \sum_{i | j = k, i & j = 0} a_i * b_j
  int n = 1 << L;
  for (int i = 1; i < n; ++i)
    ct[i] = ct[i & (i - 1)] + 1;
  for (int i = 0; i < n; ++i)
    f[ct[i]][i] = a[i], g[ct[i]][i] = b[i];
  for (int i = 0; i <= L; ++i)
    fwt(f[i], n, 1), fwt(g[i], n, 1);
  for (int i = 0; i <= L; ++i)
    for (int j = 0; j <= i; ++j)
      for (int x = 0; x < n; ++x)
        h[i][x] = (h[i][x] + f[j][x] * g[i-j][x]) % mod;
  for (int i = 0; i <= L; ++i)
    fwt(h[i], n, mod-1);
  for (int i = 0; i < n; ++i)
    c[i] = h[ct[i]][i];
}
