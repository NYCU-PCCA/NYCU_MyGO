vector<int> kmp(const auto &s) {
  vector<int> f(s.size());
  for (int i = 1, k = 0; i < (int)s.size(); ++i) {
    while (k > 0 && s[i] != s[k]) k = f[k - 1];
    f[i] = (k += (s[i] == s[k]));
  }
  return f;
}
vector<int> search(const auto &s, const auto &t) {
  // return 0-indexed occurrence of t in s
  vector<int> f = kmp(t), r;
  for (int i = 0, k = 0; i < (int)s.size(); ++i) {
    while (k > 0 and s[i] != t[k]) k = f[k - 1];
    k += (s[i] == t[k]);
    if (k == (int)t.size())
      r.push_back(i - t.size() + 1), k = f[k - 1];
  }
  return r;
}
