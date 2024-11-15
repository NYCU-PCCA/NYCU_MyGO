template <typename T> struct M {
  static T MOD; // change to constexpr if already known
  T v;
  M(T x = 0) {
    v = (-MOD <= x and x < MOD) ? x : x % MOD;
    if (v < 0) v += MOD;
  }
  explicit operator T() const { return v; }
  bool operator==(const M &b) const { return v == b.v; }
  bool operator!=(const M &b) const { return v != b.v; }
  M operator-() { return M(-v); }
  M operator+(M b) { return M(v + b.v); }
  M operator-(M b) { return M(v - b.v); }
  M operator*(M b) { return M(i128(v) * b.v % MOD); }
  // change implementation to extgcd if MOD is not prime
  M operator/(M b) { return *this * b.inv(); }
  M pow(int b) const {
    M r(1);
    for (M a = *this; b; b >>= 1, a *= a)
      if (b & 1) r *= a;
    return r;
  }
  M inv() const { return pow(MOD - 2); }
  M operator+=(const M &b) {
    if ((v += b.v) >= MOD) v -= MOD;
    return *this;
  }
  M operator-=(const M &b) {
    if ((v -= b.v) < 0) v += MOD;
    return *this;
  }
  friend M &operator*=(M &a, M b) { return a = a * b; }
  friend M &operator/=(M &a, M b) { return a = a / b; }
};
using mint = M<int>;
// template <> int mint::MOD = 1e9+7;
// int &mod = mint::MOD;
