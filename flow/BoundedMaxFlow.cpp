// node from 0 ~ size - 1
class Graph {
 public:
  Graph( const int &size )
      : size_( size + 2 ),
        source_( size ),
        sink_( size + 1 ),
        edges_( size_ ),
        capacity_( size_, vector< int >( size_, 0 ) ),
        lower_bound_( size_, vector< int >( size_, 0 ) ),
        lower_bound_sum_( size_, 0 ) {}
  void AddEdge( int from, int to, int lower_bound, int capacity ) {
    edges_[ from ].push_back( to );
    edges_[ to ].push_back( from );

    capacity_[ from ][ to ] += capacity - lower_bound;
    lower_bound_[ from ][ to ] += lower_bound;

    lower_bound_sum_[ from ] += lower_bound;
    lower_bound_sum_[ to ] -= lower_bound;
  }
  int MaxFlow() {
    int expected_source = 0, expected_sink = 0;
    for ( int i = 0; i < source_; ++i )
      if ( lower_bound_sum_[ i ] > 0 ) {
        capacity_[ i ][ sink_ ] = lower_bound_sum_[ i ];
        edges_[ i ].push_back( sink_ );
        edges_[ sink_ ].push_back( i );
        expected_sink += lower_bound_sum_[ i ];
      }
      else if ( lower_bound_sum_[ i ] < 0 ) {
        capacity_[ source_ ][ i ] = -lower_bound_sum_[ i ];
        edges_[ source_ ].push_back( i );
        expected_source -= lower_bound_sum_[ i ];
      }
    int Flow = 0;
    while ( BFS( source_, sink_ ) )
      for ( auto &from : edges_[ sink_ ] ) {
        if ( from_[ from ] == -1 ) continue;

        from_[ sink_ ] = from;
        int current_Flow = numeric_limits< int >::max();
        for ( int i = sink_; i != source_; i = from_[ i ] )
          current_Flow = min( current_Flow, capacity_[ from_[ i ] ][ i ] );
        if ( not current_Flow ) continue;
        for ( int i = sink_; i != source_; i = from_[ i ] ) {
          capacity_[ from_[ i ] ][ i ] -= current_Flow;
          capacity_[ i ][ from_[ i ] ] += current_Flow;
        }
        Flow += current_Flow;
      }
    if ( Flow != expected_source ) return -1;
    return Flow;
  }
  int Flow( int from, int to ) { return lower_bound_[ from ][ to ] + capacity_[ to ][ from ]; }

 private:
  bool BFS( int source, int sink ) {
    queue< int > Q;
    Q.push( source );
    from_ = vector< int >( size_, -1 );
    from_[ source ] = source;

    while ( !Q.empty() ) {
      int node = Q.front();
      Q.pop();
      if ( node == sink ) continue;
      for ( auto &neighbour : edges_[ node ] )
        if ( from_[ neighbour ] == -1 && capacity_[ node ][ neighbour ] > 0 ) {
          from_[ neighbour ] = node;
          Q.push( neighbour );
        }
    }
    return from_[ sink ] != -1;
  }
  int size_, source_, sink_;
  vector< vector< int > > edges_;
  vector< vector< int > > capacity_;
  vector< vector< int > > lower_bound_;
  vector< int > lower_bound_sum_;
  vector< int > from_;
};
