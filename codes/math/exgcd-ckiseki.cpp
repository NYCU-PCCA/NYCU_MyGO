tuple<int, int, int> exgcd(int a, int b) {
  int s = 1, t = 0, u = 0, v = 1;
  while (b) {
    int q = a / b;
    swap(a -= q * b, b);
    swap(s -= q * t, t);
    swap(u -= q * v, v);
  }
  return { s, u, a };
}
