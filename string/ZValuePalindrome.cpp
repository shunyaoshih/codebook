const int N = 1000 + 10;
int len, zv[ N * 2 ];
char op[ N * 2 ];
string ip;
int main(){
  cin >> ip; len = ip.size();
  int l2 = len * 2 + 1;
  for ( int i = 0; i < l2; ++i ) {
    if ( i & 1 ) op[ i ] = ip[ i / 2 ];
    else op[ i ] = '@';
  }
  int l = 0, r = 0;
  zv[ 0 ] = 1;
  for ( int i = 1; i < l2; ++i ) {
    if ( i > r ) {
      l = r = i;
      while ( l > 0 and r < l2 - 1 and op[ l - 1 ] == op[ r + 1 ] )
        --l, ++r;
      zv[ i ] = r - l + 1;
    }
    else {
      int md = ( l + r ) / 2, j = md + md - i;
      zv[ i ] = zv[ j ];
      int q = zv[ i ] / 2, nr = i + q;
      if ( nr == r ) {
        l = i + i - r;
        while ( l > 0 and r < l2 - 1 and op[ l - 1 ] == op[ r + 1 ] )
          --l, ++r;
        zv[ i ] = r - l + 1;
      }
      else if ( nr > r )
        zv[ i ] = ( r - i ) * 2 + 1;
    }
  }
}
