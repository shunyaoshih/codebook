// Build: O( V^2 ), Query: O( 1 )
// n: the number of nodes
int graph[ N ][ N ], lca[ N ][ N ];
vector< bool > visit( N, false );

void tarjan( int now ) {
  if ( visit[ now ] ) return;
  visit[ now ] = true;

  for ( int i = 1; i <= n; ++i )
    if ( visit[ i ] ) lca[ now ][ i ] = lca[ i ][ now ] = st.Find( i );

  for ( int i = 1; i <= n; ++i )
    if ( g[ now ][ i ] < 1e9 && !visit[ i ] ) {
      tarjan( i );
      st.Union( i, now );
    }
}
