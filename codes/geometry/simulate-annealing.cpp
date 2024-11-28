f80 anneal() { // calc, p, p_prime
  uniform_real_distribution<f80> rnd(0, 1);
  const f80 dT = 0.001; mt19937 reng(seed);
  // Argument p
  f80 S_cur = calc(p), S_best = S_cur;
  for (f80 T = 2000; T > EPS; T -= dT) {
    // auto p_prime = p + { T * (r() * 2 - 1) };
    const f80 S_prime = calc(p_prime);
    const f80 delta_c = S_prime - S_cur;
    f80 prob = min((f80)1, exp(-delta_c / T));
    if (rnd(reng) <= prob)
      S_cur = S_prime, p = p_prime;
    if (S_prime < S_best) // find min
      S_best = S_prime, p_best = p_prime;
  }
  return S_best;
}
