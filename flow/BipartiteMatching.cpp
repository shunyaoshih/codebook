struct BipartiteMatching {  // O( ( V + E ) * sqrt( V ) )
  vector< int > G[ N ];     // N = total number of nodes = n + m
  int n, m, match[ N ], dist[ N ];
  // n: number of nodes on left side, nodes are numbered 1 to n
  // m: number of nodes on right side, nodes are numbered n+1 to n+m
  // G = NIL[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]
  bool BFS() {
    queue< int > Q;
    for ( int i = 1; i <= n; i++ ) {
      if ( match[ i ] == 0 ) {
        dist[ i ] = 0;
        Q.push( i );
      }
      else
        dist[ i ] = INF;
    }
    dist[ 0 ] = INF;
    while ( !Q.empty() ) {
      int u = Q.front();
      Q.pop();
      if ( dist[ u ] < dist[ 0 ] )
        for ( int v : G[ u ] )
          if ( dist[ match[ v ] ] == INF ) {
            dist[ match[ v ] ] = dist[ u ] + 1;
            Q.push( match[ v ] );
          }
    }
    return ( dist[ 0 ] != INF );
  }
  bool DFS( int u ) {
    if ( u != 0 ) {
      for ( int v : G[ u ] )
        if ( dist[ match[ v ] ] == dist[ u ] + 1 && DFS( match[ v ] ) ) {
          match[ v ] = u;
          match[ u ] = v;
          return true;
        }
      dist[ u ] = INF;
      return false;
    }
    return true;
  }
  int Max_Match() {
    int matching = 0;
    fill_n( match, n + m + 1, 0 );
    while ( BFS() )
      for ( int i = 1; i <= n; i++ )
        if ( match[ i ] == 0 && DFS( i ) ) matching++;
    return matching;
  }
  void AddEdge( int u, int v ) { G[ u ].push_back( n + v ); }
  void DFS2( int u ) {
    dist[ u ] = 1;
    for ( int v : G[ u ] )
      if ( v != match[ u ] ) {
        dist[ v ] = 1;
        if ( match[ v ] != 0 ) DFS2( match[ v ] );
      }
  }
  void Min_Vertex_Cover( vector< int > &lrtn, vector< int > &rrtn ) {
    // after calling Max_Match
    fill_n( dist + 1, n + m, 0 );
    for ( int i = 1; i <= n; i++ )
      if ( match[ i ] == 0 ) DFS2( i );
    for ( int i = 1; i <= n; i++ )
      if ( dist[ i ] == 0 ) lrtn.push_back( i );
    for ( int i = n + 1; i <= n + m; i++ )
      if ( dist[ i ] == 1 ) rrtn.push_back( i - n );
  }
} ob;
