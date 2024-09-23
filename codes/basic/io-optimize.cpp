static inline int gc() {
  constexpr int B = 1<<20; static char buf[B], *p, *q;
  if (p == q) q = (p = buf) + fread(buf, 1, B, stdin);
  return q == buf ? EOF : *p++;
}
