// next permutation of x as a bit sequence
u64 next_bits_permutation(u64 x) {
  u64 c = __builtin_ctzll(x), r = x + (u64(1) << c);
  return (r ^ x) >> (c + 2) | r;
}
// iterate over all (proper) subsets of bitset s
void subsets(u64 s) {
  for (u64 x = s; x;) { --x &= s; /* do stuff */ }
}
