int solve_crt(int x1, int m1, int x2, int m2) {
  int g = gcd(m1, m2);
  if((x2 - x1) % g) return -1; // no sol
  m1 /= g; m2 /= g;
  auto [pa,pb] = extgcd(m1, m2);
  int lcm = m1 / g * m2;
  int res = pa * (x2 - x1) * m1 + x1;
  return (res % lcm + lcm) % lcm;
}
