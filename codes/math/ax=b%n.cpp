vector<int> mod_leq(int a, int b, int n) {
  vector<int> rt;
  int g = gcd(a, n);
  pii p = exgcd(a, n);
  if (!(b % g)) {
    p.X = p.X * (b / g) % n;
    for (int i = 0; i < g; ++i)
      rt.eb(p.X), p.X = (p.X + n / g) % n;
  }
  return rt;
}
