#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/assoc_container.hpp> // rb_tree
using namespace __gnu_pbds;
// heap tags: paring/binary/binomial/rc_binomial/thin
template<typename T>
using pbds_heap = __gnu_pbds::prioity_queue<T, less<T>, pairing_heap_tag>;
// pbds_heap::point_iterator
// x = pq.push(10); pq.modify(x, 87); a.join(b);
template<typename T, typename U = null_type>
using rkt = tree<T, U, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#include <tr2/dynamic_bitset>
// tr2::dynamic_bitset<> bs(n); (same as bitset)
mt19937_64 rng(int(chrono::steady_clock::now().time_since_epoch().count()));
// [0,n), [l,r]
template<typename T> T randint(T l, T r) {
  return uniform_int_distribution<T>(l,r)(rng); }
auto randint(auto n) { return randint(0,n-1); }
// comparator overload
auto cmp=[](seg a,seg b){ return a.func() < b.func();};
set<seg, decltype(cmp)> s(cmp);
map<seg, int, decltype(cmp)> mp(cmp);
priority_queue<seg,vector<seg>,decltype(cmp)> pq(cmp);
struct hasher { // hash func overload
  size_t operator()(const pii &p) const {
    return p.ft * 2 + p.sd * 3; }
}; // T = pii, operator==
unordered_map<pii, int, hasher> hsh;
int main() {
  heap h1, h2; h1.push(1), h1.push(3);
  h2.push(2), h2.push(4); h1.join(h2);
  cerr << h1.size() << h2.size() << h1.top(); // 404
  rkt<int> st; for (int x : {0, 2, 3, 4}) st.insert(x);
  cerr<<*st.find_by_order(2)<<st.order_of_key(1);//31
  // shuffle(ALL(v),rng);
} // __int128_t,__float128_t
