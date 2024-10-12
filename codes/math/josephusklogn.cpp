int josephus(int n, int k) {
  if (n == 1) return 0;
  if (k == 1) return n - 1;
  if (k > n) return (josephus(n - 1, k) + k) % n;
  int res = josephus(n - n / k, k);
  res -= n % k;
  if (res < 0) res += n;             /// mod n
  else         res += res / (k - 1); /// 還原
  return res;
}
