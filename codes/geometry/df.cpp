const ld PI = acosl(-1);
const ld eps = 1e-9;
bool isZ(ld x) { return -eps < x and x < eps; }
bool isZ(ll x) { return x == 0; }
template<typename T>
struct Pt {
  using P = Pt; T x, y;
  Pt() {}
  Pt(T _x, T _y): x(_x), y(_y) {}
  template<typename U>
  Pt<U> to() const { return Pt<U>(x, y); }
  operator Pt<ld>() const { return to<ld>(); }
  P operator+(P o) {return P{x+o.x,y+o.y};}
  P operator-(P o) {return P{x-o.x,y-o.y};}
  P operator*(T k) {return P{x*k, y*k};}
  P operator/(T k) {return P{x/k, y/k};}
  bool operator==(P o) {
    return isZ(x-o.x) and isZ(y-o.y); }
  T dot(P o) { return x*o.x + y*o.y; }
  T cross(P o) { return x*o.y - y*o.x; }
  P normal() { return P{-y,x}; }
  T abs2() { return dot(*this); }
  ld abs() { return sqrtl(abs2()); }
  ld rad(P o) {
    return fabs(atan2(fabs(cross(o)),dot(o))); }
  ld ang() { ld A = atan2(y,x);
    return A <= -PI/2 ? A+PI*2 : A; }
};
