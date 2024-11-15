union di { f64 d; u64 i; };
// binary search in [L, R) with relative error 2^-eps
f64 bsearch(f64 L, f64 R, int eps, auto &chk) {
  di l = {L}, r = {R}, m;
  while (r.i - l.i > 1LL << (52 - eps)) {
    m.i = (l.i + r.i) >> 1;
    if (chk(m.d)) r = m;
    else l = m;
  }
  return l.d;
}
