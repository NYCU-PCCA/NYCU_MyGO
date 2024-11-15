// only works for integer coordinates!!
struct Line {
    mutable int a, b, p;
    bool operator<(const Line &rhs) const { return a < rhs.a; }
    bool operator<(int x) const { return p < x; }
};
struct DynamicHull : multiset<Line, less<>> {
    static const int kInf = 1e18;
    int Div(int a, int b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x -> p = kInf; return 0; }
        if (x -> a == y -> a) x -> p = x -> b > y -> b ? kInf : -kInf;
        else x -> p = Div(y -> b - x -> b, x -> a - y -> a);
        return x -> p >= y -> p;
    }
    void addline(int a, int b) {
        auto z = insert({a, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x) -> p >= y -> p) isect(x, erase(y));
    }
    int query(int x) {
        auto l = *lower_bound(x);
        return l.a * x + l.b;
    }
};
