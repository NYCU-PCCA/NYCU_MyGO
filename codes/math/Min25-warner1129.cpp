#include <bits/stdc++.h>
 
using namespace std;

template<class F, class S>
ostream &operator<<(ostream &s, const pair<F, S> &v) {
    s << "(" << v.first << ", " << v.second << ")";
    return s;
}
template<ranges::range T> requires (!is_convertible_v<T, string_view>)
istream &operator>>(istream &s, T &&v) { 
    for (auto &&x : v) s >> x; 
    return s; 
}
template<ranges::range T> requires (!is_convertible_v<T, string_view>)
ostream &operator<<(ostream &s, T &&v) { 
    for (auto &&x : v) s << x << ' '; 
    return s; 
}
 
#ifdef LOCAL
template<class... T> void dbg(T... x) {
    char e{};
    ((cerr << e << x, e = ' '), ...);
}
#define debug(x...) dbg(#x, '=', x, '\n')
#else
#define debug(...) ((void)0)
#endif
 
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define ff first
#define ss second
 
template<class T> inline constexpr T inf = numeric_limits<T>::max() / 2;
bool chmin(auto &a, auto b) { return (b < a and (a = b, true)); }
bool chmax(auto &a, auto b) { return (a < b and (a = b, true)); }
 
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

constexpr i64 mod = 1E9 + 7;

template<size_t N>
struct Comb {
    array<i64, N + 1> fac, ifac, inv;
    Comb() : fac{1, 1}, ifac{1, 1}, inv{0, 1} {
        for (int i = 2; i <= N; i++) {
            inv[i] = inv[mod % i] * (mod - mod / i) % mod;
            fac[i] = fac[i - 1] * i % mod;
            ifac[i] = ifac[i - 1] * inv[i] % mod;
        }
    }
    i64 operator()(int n) {
        return n < 0 ? ifac[-n] : fac[n];
    }
    i64 operator()(int n, int m) {
        if (n < m or m < 0) return 0;
        return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
};
Comb<200005 * 30> comb;

vector<int> primes, minp;
vector<bool> isp;
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    isp.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            isp[i] = 1;
            primes.push_back(i);
        }
        for (i64 p : primes) {
            if (p * i > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}

// Prefix Sums of Multiplicative Functions
// O(N^0.75 / logN)
// calc f(1) + ... + f(N)
// where f is multiplicative function
// construct completely multiplicative functions 
// g_i s.t. for all prime x, f(x) = sigma c_i*g_i(x)
// def gsum(x) = g(1) + ... + g(x)
// call apply(g_i, gsum_i, c_i) and call work(f)
struct Min25 {
    const i64 N, sqrtN;
    vector<i64> Q;
    vector<i64> Fp, S;
    int id(i64 x) { return x <= sqrtN ? Q.size() - x : N / x - 1; }
    Min25(i64 N) : N(N), sqrtN(sqrtl(N)) {
        sieve(sqrtN);
        for (i64 l = 1, r; l <= N; l = r + 1) {
            Q.push_back(N / l);
            r = N / (N / l);
        }
        Fp.assign(Q.size(), 0);
        S.assign(Q.size(), 0);
    }
    void apply(const auto &f, const auto &fsum, i64 coef) {
        vector<i64> F(Q.size());
        for (int i = 0; i < Q.size(); i++) {
            F[i] = fsum(Q[i]) - 1;
        }
        for (i64 p : primes) {
            auto t = F[id(p - 1)];
            for (int i = 0; i < Q.size(); i++) {
                if (Q[i] < p * p) {
                    break;
                }
                F[i] -= (F[id(Q[i] / p)] - t) * f(p);
                F[i] %= mod;
            }
        }
        for (int i = 0; i < Q.size(); i++) {
            (Fp[i] += F[i] * coef) %= mod;
        }
    }
    i64 work(const auto &f) {
        S = Fp;
        for (i64 p : primes | views::reverse) {
            i64 t = Fp[id(p)];
            for (int i = 0; i < Q.size(); i++) {
                if (Q[i] < p * p) {
                    break;
                }
                for (i64 pw = p, c = 1; pw * p <= Q[i]; pw *= p, c++) {
                    S[i] += (S[id(Q[i] / pw)] - t) * f(c);
                    S[i] %= mod;
                    S[i] += f(c + 1);
                    S[i] %= mod;
                }
            }
        }
        for (int i = 0; i < Q.size(); i++) {
            S[i]++;
        }
        return S[0];
    }
};

void solve() {
    int n, k, d;
    cin >> n >> k >> d;

    Min25 M(n);
    M.apply(
        [&](i64 x) { return 1; },
        [&](i64 x) { return x; } ,
        comb(k + d, d));

    i64 ans = M.work([&](i64 c) {
            return comb(c * k + d, d);
        });

    ans = (ans % mod + mod) % mod;

    cout << ans << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

