class SuffixArray {
  public:
    static const int N = 1e5 + 10;
    string st;
    int SA[ N ], RA[ N ], tempSA[ N ], tempRA[ N ], counting[ N ], n;
    int LCP[ N ], PLCP[ N ], Phi[ N ];

    void build( string& s ) { st = s + '.'; n = st.size(); constructSA(); constructLCP(); }
    void countingSort( int k ){
      int maxRange = max( 260, n );
      memset( counting, 0, sizeof counting );
      for ( int i = 0; i < n; i++ )
        counting[ i + k < n ? RA[ i + k ] : 0 ]++;

      int sum = 0;
      for ( int i = 0; i < maxRange; ++i ) {
        int temp = counting[ i ];
        counting[ i ] = sum;
        sum += temp;
      }

      for ( int i = 0 ; i < n; ++i )
        tempSA[ counting[ SA[ i ] + k < n ? RA[ SA[ i ] + k ] : 0 ]++ ] = SA[ i ];
      for ( int i = 0; i < n; ++i )
        SA[ i ] = tempSA[ i ];
    }
    void constructSA() {
      for ( int i = 0; i < n; ++i ) {
        SA[ i ] = i;
        RA[ i ] = st[ i ];
      }

      for ( int k = 1; k < n; k <<= 1 ) {
        countingSort( k ); countingSort( 0 );
        int rank;
        tempRA[ SA[ 0 ] ] = rank = 0;
        for ( int i = 1; i < n; ++i )
          tempRA[ SA[ i ] ] = ( RA[ SA[ i - 1 ] ] == RA[ SA[ i ] ] && RA[ SA[ i - 1 ] + k ] == RA[ SA[ i ] + k ] ) ? rank : ++rank;
        for ( int i = 0; i < n; ++i ) RA[ i ] = tempRA[ i ];
        if ( RA[ SA[ n - 1 ] ] == n - 1 ) break;
      }
    }
    void constructLCP() {
      Phi[ SA[ 0 ] ] = -1;
      for ( int i = 1; i < n; ++i )
        Phi[ SA[ i ] ] = SA[ i - 1 ];
      int L = 0;
      for ( int i = 0; i < n; ++i ) {
        if ( Phi[ i ] == -1 ) {
          PLCP[ i ] = 0;
          continue;
        }
        while ( st[ i + L ] == st[ Phi[ i ] + L ] ) L++;
        PLCP[ i ] = L;
        L = max( L - 1, 0 );
      }
      for ( int i = 0; i < n; ++i ) LCP[ i ] = PLCP[ SA[ i ] ];
    }
};

