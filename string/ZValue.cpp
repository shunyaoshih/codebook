void Z_value( string& s, vector< int >& z ) {
  z.resize( s.size() );
  int i, j, left, right, len = s.size();
  left = right = 0; z[ 0 ] = len;
  for ( i = 1; i < (int)s.size(); ++i ) {
    j = max( min( z[ i - left ], right - i ), 0 );
    for( ; i + j < len && s[ i + j ] == s[ j ]; ++j );
    z[ i ] = j;
    if( i + z[ i ] > right ) {
      left = i;
      right = i + z[ i ];
    }
  }
}
