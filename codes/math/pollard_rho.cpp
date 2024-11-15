int pollard(int n) {
  auto f = [n](int x){ return (x * x % n) + 1; };
  int x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  while (t++ % 40 || gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = (prd * abs(x-y) % n)))
      prd = q;
    x = f(x), y = f(f(y));
  }
  return gcd(prd, n);
}
