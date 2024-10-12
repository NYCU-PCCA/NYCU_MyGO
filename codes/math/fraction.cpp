/* py: from fractions import Decimal, Fraction */
template <typename T = int>
struct fraction {
  T n, d;
  fraction(T _n = 0, T _d = 1): n(_n), d(_d) {
    T g = gcd(n,d);
    n /= g; d /= g;
    if(d < 0) n *= -1, d *= -1; }
  fraction operator-() { return fraction(-n,d); }
  fraction operator+(fraction &b) {
    return fraction(n*b.d+b.n*d, d*b.d); }
  fraction operator-(fraction &b){
    return fraction(n*b.d-b.n*d, d*b.d); }
  fraction operator*(fraction &b) {
    return fraction(n*b.n, d*b.d); }
  fraction operator/(fraction &b) {
    return fraction(n*b.d, d*b.n); }
};
