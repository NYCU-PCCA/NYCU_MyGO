vector<int> Zalgo(const string &s) {
  vector<int> z(s.size(), s.size());
  for (int i = 1, l = 0, r = 0; i < z[0]; ++i) {
    int j = clamp(r - i, 0, z[i - l]);
    for (; i + j < z[0] and s[i + j] == s[j]; ++j);
    if (i + (z[i] = j) > r) r = i + z[l = i];
  }
  return z;
}
