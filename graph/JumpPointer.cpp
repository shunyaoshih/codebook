// Build: O( VlogV ), Query: O( logV )
int tin[ N ], tout[ N ], ancestor[ N ][ 20 ];
vector< int > v[ N ];

void dfs( int now, int pnow ) {
  tin[ now ] = ++now_time;

  ancestor[ now ][ 0 ] = pnow;
  for ( int i = 1 ; i < 20 ; ++i )
    ancestor[ now ][ i ] = ancestor[ ancestor[ now ][ i - 1 ] ][ i - 1 ];

  for ( auto child : v[ now ] )
    if ( child != pnow )
      dfs( child, now );

  tout[ now ] = ++now_time;
}
bool check_ancestor( int x, int y ) {
  return ( tin[ x ] <= tin[ y ] and tout[ x ] >= tout[ y ] );
}
int find_lca( int x, int y ) {
  if ( check_ancestor( x, y ) ) return x;
  if ( check_ancestor( y, x ) ) return y;

  for ( int i = 19 ; i >= 0 ; --i )
    if ( !check_ancestor( ancestor[ x ][ i ], y ) )
      x = ancestor[ x ][ i ];
  return ancestor[ x ][ 0 ];
}
