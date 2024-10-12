//(2^16)+1, 65537, 3
//7*17*(2^23)+1, 998244353, 3
//1255*(2^20)+1, 1315962881, 3
//51*(2^25)+1, 1711276033, 29
template<int P, int RT> //maxn must be 2^k
struct NTT {
  int maxn;
  vector<int> w;
  NTT(int n) {
    maxn = 2 << __lg(n+1);
    w.resize(maxn);
    int dw = mpow(RT, (P - 1) / maxn);
    w[0] = 1;
    for (int i = 1; i < maxn; ++i) w[i] = w[i - 1] * dw % P;
  }
  void bitrev(vector<int> &a) {
    int i = 0;
    for (int j = 1; j < maxn - 1; ++j) {
      for (int k = maxn >> 1; (i ^= k) < k; k >>= 1);
      if (j < i) swap(a[i], a[j]);
    }
  }
  void operator()(vector<int> &a, bool inv = false) { //0 <= a[i] < P
    bitrev(a);
    for (int L = 2; L <= maxn; L <<= 1) {
      int dx = maxn / L, dl = L >> 1;
      for (int i = 0; i < maxn; i += L) {
        for (int j = i, x = 0; j < i + dl; ++j, x += dx) {
          int tmp = a[j + dl] * w[x] % P;
          if ((a[j + dl] = a[j] - tmp) < 0) a[j + dl] += P;
          if ((a[j] += tmp) >= P) a[j] -= P;
        }
      }
    }
    if (inv) {
      reverse(1 + begin(a), end(a));
      int invn = fpow(maxn, P-2); // do fpow
      for (int i = 0; i < maxn; ++i) a[i] = a[i] * invn % P;
    }
  }
};
