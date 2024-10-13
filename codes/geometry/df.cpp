const ld PI = acosl(-1);
const ld eps = 1e-9;
bool isZ(double x) { return -eps < x and x < eps; }
bool isZ(int x) { return x == 0; }
template<typename T>
struct Pt {
  using P = Pt; T x, y;
  Pt() {}
  Pt(T _x, T _y): x(_x), y(_y) {}
  template<typename U>
  Pt<U> to() { return Pt<U>(x, y); }
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

template<typename T>
struct line {
  using P = Pt<T>; P p1, p2; T a, b, c; // ax+bc = c
  line() {}
  line(P x, P y): p1(x), p2(y) {}
  void pton() { a = p1.y - p2.y; b = p2.y - p1.y;
    c = a * p1.x + b * p1.y; }
  // >0 left | =0 on line | <0 right
  T ori(P p) {return (p2-p1).cross(p-p1);}
  // 點投影落在線段上 <= 0
  T btw(P p) { return(p1-p).dot(p2-p); }
  bool p_on_seg(P p) {
    return ori(p) == 0 and btw(p) <= 0; }
  T dis2(P p, bool is_seg = false) {
    P v = p2 - p1, v1 = p - p1;
    if (is_seg) {
      P v2 = p - p2;
      if (v.dot(v1) <= 0) return v1.abs2();
      if (v.dot(v2) >= 0) return v2.abs2();
    }
    T t = v.cross(v1);
    return t * t / v.abs2();
  }
	T seg_dis2(line l) {
		return min({ dis2(l.p1, 1), dis2(l.p2, 1),
        l.dis2(p1, 1), l.dis2(p2, 1) });
	}
	P projection(P p) {
		P n = (p2-p1).normal();
		return p-n*(p-p1).dot(n)/n.abs2();
	}
	P mirror(P p) { // require pton()
    auto a2 = a*a, b2 = b*b, d = a2 + b2;
    return {
      (b2*p.x - a2*p.x - 2*a*b*p.y - 2*a*c) / d,
		  (a2*p.y - b2*p.y - 2*a*b*p.x - 2*b*c) / d
    }; }
	bool equal(line l) {
		return ori(l.p1) == 0 and ori(l.p2) == 0; }
	bool parallel(line l) {
		return (p1-p2).cross(l.p1-l.p2) == 0; }
	bool cross_seg(line l) { return
    (p2-p1).cross(l.p1-p1) *
    (p2-p1).cross(l.p2-p1) <= 0; } // 直線交線段
	int line_intersect(line l) { // -1 same, 1 one, 0 no
		return parallel(l)? (ori(l.p1) == 0 ? -1 : 0) : 1;}
	int seg_intersect(line l) {
    T c1 = ori(l.p1), c3 = l.ori(p1);
    T c2 = ori(l.p2), c4 = l.ori(p2);
		if(c1 == 0 and c2 == 0) { // 共線
			bool b1 = btw(l.p1) >= 0, b2 = btw(l.p2) >= 0;
			T a3 = l.btw(p1), a4 = l.btw(p2);
			if(b1 and b2 and a3 == 0 and a4 >= 0) return 2;
			if(b1 and b2 and a3 >= 0 and a4 == 0) return 3;
			if(b1 and b2 and a3 >= 0 and a4 >= 0) return 0;
			return -1; // 無限交點
		} else if (c1 * c2 <= 0 and c3 * c4 <= 0) return 1;
		return 0; // 不相交
	}
	P line_intersection(line l) { // 直線交點
		P v1 = p2 - p1, v2 = l.p2 - l.p1, v3 = l.p1 - p1;
		// if(v1.cross(v2) == 0) return INF;
		return p1 + v1 * (v3.cross(v2) / v1.cross(v2));
	}
	P seg_intersection(line l) { // 線段交點
		int res = seg_intersect(l);
		if(res <= 0) assert(false);
		if(res == 2) return p1;
		if(res == 3) return p2;
		return line_intersection(l);
	}
};

template<typename T, T INF = numeric_limits<T>::max()>
struct polygon {
  using P = Pt<T>; using L = line<T>;
	polygon(){}
	vector<P> p; // 逆時針順序
	T area() const { // 面積
		T ans = 0;
		for(size_t sz=p.size(), i=sz-1, j=0; j < sz; i=j++)
			ans += p[i].cross(p[j]);
		return ans / 2;
	}
	P center_of_mass() { // 重心
		T cx=0, cy=0, w=0;
		for(size_t sz=p.size(), i=sz-1, j=0; j < sz;i=j++){
			T a = p[i].cross(p[j]);
			cx += (p[i].x + p[j].x) * a;
			cy += (p[i].y + p[j].y) * a;
			w += a;
		}
		return { cx/3/w, cy/3/w };
	}
	char ahas(P t) { // simple polygon
		bool c = 0; // in 1 | edge -1 |  other 0
		for(size_t sz=p.size(), i=0, j=sz-1; i < sz; j=i++)
			if (L(p[i],p[j]).p_on_seg(t)) return -1;
			else if ((p[i].y > t.y) != (p[j].y > t.y) and
			  t.x < (p[j].x - p[i].x) * (t.y - p[i].y) /
        (p[j].y - p[i].y) + p[i].x) c = !c;
		return c;
	}
	char p_in_convex(P x) { // in 1 | edge -1 |  other 0
		size_t l = 1, r = p.size() - 2;
		while(l <= r){
			int mid = (l+r)/2;
			T a1 = (p[mid  ]-p[0]).cross(x-p[0]);
			T a2 = (p[mid+1]-p[0]).cross(x-p[0]);
			if (a1 >= 0 and a2 <= 0) {
				T res = (p[mid+1]-p[mid]).cross(x-p[mid]);
				return res > 0 ? 1 : (res >= 0 ? -1 : 0);
			} else if (a1 < 0) r = mid-1;
			else l = mid+1;
		}
		return 0;
	}
	vector<T> ang() { // 凸包邊對x軸的夾角
		vector<T> res; // 一定是遞增的
    auto sz = p.size();
		for(size_t i = 0; i < sz; i++)
			res.push_back((p[(i+1)%sz] - p[i]).ang());
		return res;
	}
	bool line_intersect(vector<T>&A, L l) { // O(logN)
    ld a1 = (l.p1-l.p2).ang(), a2 = (l.p2-l.p1).ang();
    int f1 = upper_bound(ALL(A),a1)-A.begin();
    int f2 = upper_bound(ALL(A),a2)-A.begin();
		return l.cross_seg(L(p[f1],p[f2]));
	}
	polygon cut(L l) {
		polygon ans; // 凸包對直線切割，得到直線l左側的凸包
		for(size_t n=p.size(), i=n-1, j=0; j < n; i=j++) {
      bool a = l.ori(p[i]) >= 0; auto li = l.ori(p[j]);
			if (a) ans.p.push_back(p[i]);
      if ((a and li < 0) or (!a and li > 0))
					ans.p.push_back(
            l.line_intersection(L(p[i],p[j])) );
		}
		return ans;
	}
	static bool convex_cmp(P a, P b) {
		return (a.x < b.x) or (a.x == b.x and a.y < b.y);
	}
	void convex(vector<P> &v) { // counterclockwise
		sort(ALL(v), convex_cmp); // careful n <= 2
		p.resize(v.size()+1); // n = 0 RE
    int t = 0, s = 1;
    for (int x = 2; x--; s = t--, reverse(ALL(v)))
      for (P i : v) {
        while (t>s && ori(i, p[t-1], p[t-2]) >= 0) t--;
        p[t++] = i;
      }
    p.resize(t);
	}
	T diam() { // 直徑
		size_t n = p.size(), t = 1;
		T ans = 0; p.push_back(p[0]);
		for(size_t i = 0; i < n; i++) {
			P now = p[i+1] - p[i];
			while (now.cross(p[t+1]-p[i]) >
             now.cross(p[t  ]-p[i]) ) t = (t+1) % n;
			ans = max(ans,(p[i]-p[t]).abs2());
		}
		return p.pop_back(), ans;
	}
	T min_cover_rectangle() { // 最小覆蓋矩形
		size_t n = p.size(), t = 1, r = 1, l = 0;
		if(n < 3) return 0; // 也可以做最小周長矩形
		T ans = INF; p.push_back(p[0]);
		for(int i = 0; i < n; i++) {
			P now = p[i+1] - p[i];
			while (now.cross(p[t+1]-p[i]) >
             now.cross(p[t  ]-p[i]) ) t = (t+1) % n;
			while (now.dot(p[r+1]-p[i]) >
             now.dot(p[r  ]-p[i]) ) r = (r+1) % n;
			if (!i) l = r;
			while (now.dot(p[l+1]-p[i]) <=
             now.dot(p[l  ]-p[i]) ) l = (l+1) % n;
			T d = now.abs2();
			T tmp = now.cross(p[t]-p[i]) *
        (now.dot(p[r]-p[i]) - now.dot(p[l]-p[i])) / d;
			chmin(ans, tmp);
		}
		return p.pop_back(), ans;
	}
	T dis2(polygon &pl) { //凸包最近距離平方
		auto &P = p, &Q = pl.p;
		size_t n = P.size(), m = Q.size(), l = 0, r = 0;
    for(size_t i = 0; i < n; i++)if(P[i].y<P[l].y) l=i;
    for(size_t i = 0; i < m; i++)if(Q[i].y<Q[r].y) r=i;
		P.push_back(P[0]), Q.push_back(Q[0]);
		T ans = INF;
		for(size_t i = 0; i < n; i++) {
			while ((P[l]-P[l+1]).cross(Q[r+1]-Q[r]) < 0)
        r = (r+1) % m;
      L l1(P[l], P[l+1]), l2(Q[r], Q[r+1]);
			chmin(ans, l1.seg_dis2(l2));
			l = (l+1) % n;
		}
		return P.pop_back(), Q.pop_back(), ans;
	}
	static char sign(P t) {
		return (t.y == 0 ? t.x : t.y) < 0;
	}
	static bool angle_cmp(L A, L B) {
		P a = A.p2 - A.p1, b = B.p2 - B.p1;
		return sign(a) < sign(b) or
      (sign(a) == sign(b) and a.cross(b) > 0);
	}
	int halfplane_intersection(vector<L> &s){
		sort(ALL(s), angle_cmp); // 線段左側為該線段半平面
		int l, r, n = s.size();
		vector<P> px(n); vector<L> q(n);
		q[l=r=0] = s[0];
		for (int i = 1; i < n; i++) {
			while (l < r and s[i].ori(px[r-1]) <= 0) --r;
			while (l < r and s[i].ori(px[l]) <= 0) ++l;
			q[++r] = s[i];
			if (q[r].parallel(q[r-1])) {
				--r;
				if (q[r].ori(s[i].p1) > 0) q[r] = s[i];
			}
			if (l<r) px[r-1]= q[r-1].line_intersection(q[r]);
		}
		while (l < r and q[l].ori(px[r-1]) <= 0) --r;
		p.clear();
		if (r-l <= 1) return 0;
		px[r] = q[r].line_intersection(q[l]);
		for (int i = l; i <= r; i++) p.push_back(px[i]);
		return r-l+1;
	}
};

template<typename T>
struct triangle {
  using P = Pt<T>; P a, b, c;
	triangle() {}
	triangle(P _a, P _b, P _c): a(_a), b(_b), c(_c) {}
	T area() {
		T t = (b-a).cross(c-a)/2;
		return t > 0 ? t : -t;
	}
	P barycenter() { // 重心
		return (a + b + c)/3; }
	P circumcenter() { // 外心
    auto hab = (a+b)/2, hac = (a+c)/2;
		line<T> u{ hab, { hab.x-a.y+b.y, hab.y+a.x-b.x } };
		line<T> v{ hac, { hac.x-a.y+c.y, hac.y+a.x-c.x } };
		return u.line_intersection(v);
	}
	P incenter() { // 內心
		T A = sqrt((b-c).abs2());
    T B = sqrt((a-c).abs2());
    T C = sqrt((a-b).abs2());
    P r{ A*a.x + B*b.x + C*c.x, A*a.y + B*b.y + C*c.y};
		return r/(A +B+C);
	}
	P perpencenter() { // 垂心
		return barycenter() * 3 - circumcenter() * 2; }
};
