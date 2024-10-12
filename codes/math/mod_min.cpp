// min{k | l <= ((ak) mod m) <= r}, no solution -> -1
int mod_min(int a, int m, int l, int r) {
  if (a == 0) return l ? -1 : 0;
  if (int k = (l + a - 1) / a; k * a <= r)
    return k;
  int b = m / a, c = m % a;
  if (int y = mod_min(c, a, a - r % a, a - l % a))
    return (l + y * c + a - 1) / a + y * b;
  return -1;
}
