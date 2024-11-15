template <typename T> /// n = |a| = |rt| = 2^k
void fft_(int n, vector<T>&a, vector<T>&rt, bool inv) {
  vector<int> br(n);
  for (int i = 1; i < n; i++) {
    br[i] = (i&1) ? br[i - 1] + n / 2 : br[i / 2] / 2;
    if (br[i] > i) swap(a[i], a[br[i]]);
  }
  for (int len = 2; len <= n; len *= 2)
    for (int i = 0; i < n; i += len)
      for (int j = 0; j < len / 2; j++) {
        int pos = n / len * (inv ? len - j : j);
        T u = a[i + j], v = a[i + j + len/2] * rt[pos];
        a[i + j] = u + v, a[i + j + len/2] = u - v;
      }
  if (T minv = T(1) / T(n); inv)
    for (T &x : a) x *= minv;
}
void fft(vector<complex<double>> &a, bool inv) {
  int n = SZ(a);
  vector<complex<double>> rt(n + 1);
  double arg = acosl(-1) * 2 / n;
  for (int i = 0; i <= n; i++)
    rt[i] = {cosl(arg * i), sinl(arg * i)};
  fft_(n, a, rt, inv);
}
// (2^16)+1, 65537, 3
// 7*17*(2^23)+1, 998244353, 3
// 1255*(2^20)+1, 1315962881, 3
// 51*(2^25)+1, 1711276033, 29
void ntt(vector<mint> &a, bool inv, mint p_root) {
  int n = SZ(a);
  mint root = p_root.pow((MOD - 1) / n);
  vector<mint> rt(n + 1, 1);
  for (int i = 0; i < n; i++) rt[i+1] = rt[i] * root;
  fft_(n, a, rt, inv);
}
