using u64 = unsigned long long;
inline u64 splitmix64(u64 x) {
  // change to `static u64 x = SEED;` for DRBG
  u64 z = (x += 0x9E3779B97F4A7C15);
  z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9;
  z = (z ^ (z >> 27)) * 0x94D049BB133111EB;
  return z ^ (z >> 31);
}
