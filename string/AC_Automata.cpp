#include<bits/stdc++.h>
using namespace std;

constexpr int sizz(2000 * 1000), sigma(62);
int nx[sizz][sigma], fl[sizz], spt;
void clear_ac() { spt = 1; }
int newnode() {
  fill_n(nx[spt], sigma, 0);
  return spt++;
}
int add(const char *s, int Z) {
  for(int i(0); s[i]; ++i) {
    int c(s[i] - 1);
    if (nx[Z][c] == 0) nx[Z][c] = newnode();
    Z = nx[Z][c];
  }
  return Z;
}
int q[sizz], qe; // save BFS order
void make_fl(int root) {
  fl[root] = qe = 0;
  q[qe++] = root;
  for(int qs = 0; qs < qe;) {
    int X = q[qs++];
    for(int c = 0; c < sigma; ++c) {
      if (nx[X][c]) {
        int Xc = nx[X][c], Z = fl[X];
        while (Z && nx[Z][c] == 0)
          Z = fl[Z];
        int d = Z ? nx[Z][c] : root;
        fl[Xc] = d;
        q[qe++] = Xc;
      }
    }
  }
}
int cnt[sizz];
void walk(const char *s, int root) {
  int Z = root;
  for(int i = 0; s[i]; ++i) {
    int c = s[i] - 1;
    while (Z && nx[Z][c] == 0)
      Z = fl[Z];
    Z = Z ? nx[Z][c] : root;
    ++cnt[Z];
  }
  for (int i = qe-1; i >= 0; --i)
    cnt[fl[q[i]]] += cnt[q[i]];
}
char mapper(char c) {
  if (islower(c)) return c - 'a' + 1;
  if (isupper(c)) return c - 'A' + 27;
  return c - '0' + 53;
}
char S[2048], M[1000514];
int main() {
  int n, op[1024];
  scanf("%s %d", M, &n);
  transform(M, M+strlen(M), M, mapper);
  clear_ac();
  int root = newnode();
  for(int i = 0; i < n; ++i) {
    scanf("%s", S);
    transform(S, S + strlen(S), S, mapper);
    op[i] = add(S, root);
  }
  make_fl(root);
  walk(M, root);
  for(int i = 0; i < n; ++i)
    printf("%d\n", cnt[op[i]]);
}
