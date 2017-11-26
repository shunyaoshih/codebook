// test with CF 471 D
template< typename T >
vector< int > KMP( vector< T > target, vector< T > pattern ) {
  vector< int > match;
  if ( pattern.size() > target.size() ) return match;
  vector< int > failure_function( (int)target.size(), -1 );
  for ( int i = 1, j = failure_function[ 0 ] = -1; i < (int)pattern.size(); ++i ) {
    while ( j >= 0 and pattern[ j + 1 ] != pattern[ i ] )
      j = failure_function[ j ];
    if ( pattern[ j + 1 ] == pattern[ i ] ) j++;
    failure_function[ i ] = j;
    // KMP
    int pos = i, prv = failure_function[ pos ];
    while ( pos + 1 < (int)pattern.size() and pattern[ pos + 1 ] == pattern[ prv + 1 ] ) {
      if ( failure_function[ pos ] == -1 ) break;
      pos = prv;
      prv = failure_function[ prv ];
    }
    failure_function[ i ] = prv;
  }
  for ( int i = 0, j = -1; i < (int)target.size(); ++i ) {
    while ( j >= 0 and pattern[ j + 1 ] != target[ i ] )
      j = failure_function[ j ];
    if ( pattern[ j + 1 ] == target[ i ] ) j++;
    if ( j == (int)pattern.size() - 1 ) {
      match.push_back( i - pattern.size() + 1 );
      j = failure_function[ j ];
    }
  }
  return match;
}
