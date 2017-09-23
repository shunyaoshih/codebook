class DisjointSet {
 public:
  static const int N = 1e5 + 10;
  int p[ N ];
  void Init( int x ) {
    for ( int i = 1 ; i <= x ; ++i )
      p[ i ] = i;
  }
  int Find( int x ) {
    return x == p[ x ] ? x : p[ x ] = Find( p[ x ] );
  }
  void Union( int x, int y ) {
    p[ Find( x ) ] = Find( y );
  }
};
