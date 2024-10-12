int solve(int x1, int m1, int x2, int m2) {
  int g = gcd(m1, m2);
  if ((x2 - x1) % g) return -1; // no sol
  m1 /= g; m2 /= g;
  pii p = exgcd(m1, m2);
  int lcm = m1 * m2 * g;
  int res = p.first * (x2 - x1) * m1 + x1;
  // be careful with overflow
  return (res % lcm + lcm) % lcm;
}
