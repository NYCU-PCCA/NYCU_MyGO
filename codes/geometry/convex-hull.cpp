void convex_hull(vector<Pt> &dots) {
  sort(ALL(dots));
  vector<Pt> A(1, dots[0]);
  const int sz = dots.size();
  for(int c = 0; c < 2; reverse(ALL(dots)), c++)
    for(int i = 1, t = A.size(); i < sz;
            A.eb(dots[i++]))
      while (A.size() > t and
          ori(A[A.size()-2], A.back(), dots[i]) <= 0)
        A.pb();
  A.pb(), A.swap(dots);
} // dots.size() changed !!!
