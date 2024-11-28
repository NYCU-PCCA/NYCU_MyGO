#ifdef DEBUG
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) debug_(__LINE__,#a, a)
void debug_(auto n, auto s, auto ...a) {
  cerr << "\e[1;32mline " << n << "(" << s << ") = (";
  int f = 0;
  (..., (cerr << (f++ ? ", " : "") << a));
  cerr << ")\e[0m\n";
}
#include <experimental/iterator>
#define orange(a...) orange_(__LINE__,#a, a)
void orange_(auto n, auto s, auto L, auto R) {
  cerr << "\e[1;33mline " << n << "[" << s << "] = [";
  using namespace experimental;
  copy(L, R, make_ostream_joiner(cerr, ", "));
  cerr << "]\e[0m\n";
}
#else
#define safe ((void)0)
#define debug(...) safe
#define orange(...) safe
#endif
