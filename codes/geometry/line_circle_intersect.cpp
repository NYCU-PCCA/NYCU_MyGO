vector<Pt> circleLine(Pt c, double r, Pt l1, Pt l2) {
  Pt p = l1 + (l2-l1) * dot(c-l1, l2-l1) / abs2(l2-l1);
  double s = cross(l2-l1, c-l1);
  double h2 = r*r - s*s / abs2(l2-l1);
  if (h2 <  0) return {};
  if (h2 == 0) return {p};
  Pt h = (l2 - l1) / abs(l2-l1) * sqrtl(h2);
  return {p - h, p + h};
}
