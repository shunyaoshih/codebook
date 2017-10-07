void add( int n, int v ) {
  while ( n <= N ) {
    bit[ i ] += v;
    n += ( n & -n );
  }
}
int query( int n ) {
  int ans = 0;
  while ( n > 0 ) {
    ans += bit[ n ];
    n -= ( n & -n );
  }
  return ans;
}
