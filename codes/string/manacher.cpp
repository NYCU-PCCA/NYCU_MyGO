vector<int> manacher(const string &S) {
  const int n = (int)S.size(), m = n * 2 + 1;
  vector<int> z(m); string t = "%";
  t.reserve(m); for(char c: S) t += c, t += '%';
  for (int i = 1, l = 0, r = 0; i < m; ++i) {
    z[i] = (r > i ? min(z[2 * l - i], r - i) : 1);
    while (i - z[i] >= 0 and i + z[i] < m) {
      if (t[i - z[i]] == t[i + z[i]]) z[i]++;
      else break;
    }
    if (i + z[i] > r) r = i + z[i], l = i;
  }
  return z; // the palindrome lengths are z[i] - 1
}
/* for (int i = 1; i + 1 < m; ++i) {
   int l = (i - z[i] + 2) / 2, r = (i + z[i]) / 2;
   if (l != r) // [l, r) is maximal palindrome
} */
