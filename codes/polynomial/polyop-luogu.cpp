#include <bits/stdc++.h>
#define ll long long
#define all(v) v.begin(), v.end()
#define matsuri pair<int, int>
// const int iris = 1e9+7;
const int iris = 998244353;
using namespace std;
using lld = int64_t;
const int mod = iris;
int bit_ceil(int a){return 1<<__lg(a-1)+1;}
int modpow(ll a, ll b){
  ll res = 1;
  while (b){
    if (b & 1)
      res = res * a % mod;
    a = a * a % mod;
    b /= 2;
  }
  return res;
}
int get_root(int n, int P = mod){ // ensure 0 <= n < p
  if (P == 2 or n == 0)
    return n;
  auto check = [&](lld x)
  { return modpow(int(x), (P - 1) / 2); };
  if (check(n) != 1)
    return -1;
  mt19937 rnd(7122);
  lld z = 1, w;
  while (check(w = (z * z - n + P) % P) != P - 1)
    z = rnd() % P;
  const auto M = [P, w](auto &u, auto &v)
  {
    auto [a, b] = u;
    auto [c, d] = v;
    return make_pair((a * c + b * d % P * w) % P,
             (a * d + b * c) % P);
  };
  pair<lld, lld> r(1, 0), e(z, 1);
  for (int q = (P + 1) / 2; q; q >>= 1, e = M(e, e))
    if (q & 1)
      r = M(r, e);
  return int(r.first);//sqrt(n) mod P where P is prime
}
int modinv(ll a){return modpow(a, iris - 2);}
int mul(ll a, ll b){return a * b % iris;}
int add(ll a, ll b){return (a + b) % iris;}
int sub(ll a, ll b){return (a - b + iris) % iris;}

template <int mod, int G, int maxn>
struct NTT
{
  static_assert(maxn == (maxn & -maxn));
  int roots[maxn];
  NTT()
  {
    int r = modpow(G, (mod - 1) / maxn);
    for (int i = maxn >> 1; i; i >>= 1)
    {
      roots[i] = 1;
      for (int j = 1; j < i; j++)
        roots[i + j] = mul(roots[i + j - 1], r);
      r = mul(r, r);
      // for (int j = 0; j < i; j ++) // FFT (tested)
      // roots [i+j] = polar <llf >(1 , PI * j / i);
    }
  }
  // n must be 2^k, and 0 <= F[i] < mod
  void operator()(int F[], int n, bool inv = false)
  {
    for (int i = 0, j = 0; i < n; i++)
    {
      if (i < j)
        swap(F[i], F[j]);
      for (int k = n >> 1; (j ^= k) < k; k >>= 1)
        ;
    }
    for (int s = 1; s < n; s *= 2)
      for (int i = 0; i < n; i += s * 2)
        for (int j = 0; j < s; j++)
        {
          int a = F[i+j], b=mul(F[i+j+s], roots[s+j]);
          F[i + j] = add(a, b);
          F[i + j + s] = sub(a, b);
        }
    if (!inv)
      return;
    const int invn = modinv(n);
    for (int i = 0; i < n; i++)
      F[i] = mul(F[i], invn);
    reverse(F + 1, F + n);
  }
};

NTT<mod, 3, 1 << 23> ntt;

#define fi(l, r) for (size_t i = (l); i < (r); i++)
using S = vector<int>;
auto Mul(auto a, auto b, size_t sz)
{
  a.resize(sz), b.resize(sz);
  ntt(a.data(), sz);
  ntt(b.data(), sz);
  fi(0, sz) a[i] = mul(a[i], b[i]);
  return ntt(a.data(), sz, true), a;
}
S Newton(const S &v, int init, auto &&iter)
{
  S Q = {init};
  for (int sz = 2; Q.size() < v.size(); sz *= 2)
  {
    S A{begin(v), begin(v) + min(sz, int(v.size()))};
    A.resize(sz * 2), Q.resize(sz * 2);
    iter(Q, A, sz * 2);
    Q.resize(sz);
  }
  return Q.resize(v.size()), Q;
}
S Inv(const S &v)
{ // v[0] != 0
  return Newton(v, modinv(v[0]),
          [](S &X, S &A, int sz)
          {
    ntt(X.data(), sz), ntt(A.data(), sz);
    for (int i = 0; i < sz; i++)
    X[i] = mul(X[i], sub(2, mul(X[i], A[i])));
    ntt(X.data(), sz, true); });
}
S Dx(S A)
{
  fi(1, A.size()) A[i - 1] = mul(i, A[i]);
  return A.empty() ? A : (A.pop_back(), A);
}
S Sx(S A)
{
  A.insert(A.begin(), 0);
  fi(1, A.size()) A[i] = mul(modinv(int(i)), A[i]);
  return A;
}
S Ln(const S &A)
{ // coef[0] == 1; res[0] == 0
  auto B = Sx(Mul(Dx(A),Inv(A),bit_ceil(A.size()*2)));
  return B.resize(A.size()), B;
}
S Exp(const S &v)
{ // coef[0] == 0; res[0] == 1
  return Newton(v, 1,
          [](S &X, S &A, int sz)
          {
    auto Y = X; Y.resize(sz / 2); Y = Ln(Y);
    fi(0, Y.size()) Y[i] = sub(A[i], Y[i]);
    Y[0] = add(Y[0], 1); X = Mul(X, Y, sz); });
}
S Pow(S a, lld M)
{ // period mod*(mod-1)
  assert(!a.empty() && a[0] != 0);
  const auto imul = [&a](int s)
  {
  for (int &x: a) x = mul(x, s); };
  int c = a[0];
  imul(modinv(c));
  a = Ln(a);
  imul(int(M % mod));
  a = Exp(a);
  imul(modpow(c, int(M % (mod - 1))));
  return a; // mod x^N where N=a.size()
}
S Sqrt(const S &v)
{ // need: QuadraticResidue
  assert(!v.empty() && v[0] != 0);
  const int r = get_root(v[0]);
  assert(r != -1);
  return Newton(v, r,
          [](S &X, S &A, int sz)
          {
    auto Y = X; Y.resize(sz / 2);
    auto B = Mul(A, Inv(Y), sz);
    for (int i = 0, inv2 = mod / 2 + 1; i < sz; i++)
    X[i] = mul(inv2, add(X[i], B[i])); });
}
S Mul(auto &&a, auto &&b)
{
  const auto n = a.size() + b.size() - 1;
  auto R = Mul(a, b, bit_ceil(n));
  return R.resize(n), R;
}
S MulT(S a, S b, size_t k)
{
  assert(b.size());
  reverse(all(b));
  auto R = Mul(a, b);
  R = vector(R.begin() + b.size() - 1, R.end());
  return R.resize(k), R;
}
S Eval(const S &f, const S &x)
{
  if (f.empty())
    return vector(x.size(), 0);
  const int n = int(max(x.size(), f.size()));
  auto q = vector(n * 2, S(2, 1));
  S ans(n);
  fi(0, x.size()) q[i + n][1] = sub(0, x[i]);
  for (int i = n - 1; i > 0; i--)
    q[i] = Mul(q[i << 1], q[i << 1 | 1]);
  q[1] = MulT(f, Inv(q[1]), n);
  for (int i = 1; i < n; i++)
  {
    auto L = q[i << 1], R = q[i << 1 | 1];
    q[i << 1 | 0] = MulT(q[i], R, L.size());
    q[i << 1 | 1] = MulT(q[i], L, R.size());
  }
  for (int i = 0; i < n; i++)
    ans[i] = q[i + n][0];
  return ans.resize(x.size()), ans;
}
pair<S, S> DivMod(const S &A, const S &B)
{
  assert(!B.empty() && B.back() != 0);
  if (A.size() < B.size())
    return {{}, A};
  const auto sz = A.size() - B.size() + 1;
  S X = B;
  reverse(all(X));
  X.resize(sz);
  S Y = A;
  reverse(all(Y));
  Y.resize(sz);
  S Q = Mul(Inv(X), Y);
  Q.resize(sz);
  reverse(all(Q));
  X = Mul(Q, B);
  Y = A;
  fi(0, Y.size()) Y[i] = sub(Y[i], X[i]);
  while (Y.size() && Y.back() == 0)
    Y.pop_back();
  while (Q.size() && Q.back() == 0)
    Q.pop_back();
  return {Q, Y};
} // empty means zero polynomial
int LinearRecursionKth(S a, S c, int64_t k)
{
  const auto d = a.size();
  assert(c.size() == d + 1);
  const auto sz = bit_ceil(2 * d + 1), o = sz / 2;
  S q = c;
  for (int &x : q)
    x = sub(0, x);
  q[0] = 1;
  S p = Mul(a, q);
  p.resize(sz);
  q.resize(sz);
  for (int r; r = (k & 1), k; k >>= 1)
  {
    fill(d + all(p), 0);
    fill(d + 1 + all(q), 0);
    ntt(p.data(), sz);
    ntt(q.data(), sz);
    for (size_t i = 0; i < sz; i++)
      p[i] = mul(p[i], q[(i + o) & (sz - 1)]);
    for (size_t i = 0, j = o; j < sz; i++, j++)
      q[i] = q[j] = mul(q[i], q[j]);
    ntt(p.data(), sz, true);
    ntt(q.data(), sz, true);
    for (size_t i = 0; i < d; i++)
      p[i] = p[i << 1 | r];
    for (size_t i = 0; i <= d; i++)
      q[i] = q[i << 1];
  } // Bostan-Mori
  return mul(p[0], modinv(q[0]));
} // a_n = \sum c_j a_(n-j), c_0 is not used

void solve()
{
  int n;
  cin >> n;
  S arr(n);
  for (int &x : arr)
    cin >> x;
  arr = Ln(arr);
  for (int x : arr)
    cout << x << ' ';
}

signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T = 1;
  // cin>>T;
  while (T--)
    solve();

  return 0;
}