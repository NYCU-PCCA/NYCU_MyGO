namespace pam {
int sz, tot, last;
int ch[MAXN][26], len[MAXN], fail[MAXN];
int cnt[MAXN], dep[MAXN], dif[MAXN], slink[MAXN];
char s[MAXN];
int node(int l) {  // 建立一个長度為 l 的新節點
  sz++;
  memset(ch[sz], 0, sizeof(ch[sz]));
  len[sz] = l; fail[sz] = cnt[sz] = dep[sz] = 0;
  return sz;
}
void clear() {  // 初始化
  sz = -1; last = 0;
  s[tot = 0] = '$';
  node(0); node(-1);
  fail[0] = 1;
}
int getfail(int x) {  // 找到後綴回文
  while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
  return x;
}
void insert(char c) {  // 建樹
  s[++tot] = c; int i = c - 'a';
  int now = getfail(last);
  if (ch[now][i] == 0) {
    int x = node(len[now] + 2);
    fail[x] = ch[getfail(fail[now])][i];
    dep[x] = dep[fail[x]] + 1;
    ch[now][i] = x;
    dif[x] = len[x] - len[fail[x]];
    if (dif[x] == dif[fail[x]])
      slink[x] = slink[fail[x]];
    else
      slink[x] = fail[x];
  }
  last = ch[now][i];
  cnt[last]++;
}
}  // namespace pam
