#define L(X) (X<<1)
#define R(X) ((X<<1)+1)
#define mid ((l+r)>>1)

class SegmentTree {
 public:
  static const int N = 1e5 + 10;
  int arr[ N ], st[ N << 2 ], lazy[ N << 2 ];

  inline void Pull( int now ) {
    st[ now ] = max( st[ L( now ) ], st[ R( now ) ] );
  }
  inline void Push( int now, int l, int r ) {
    if ( lazy[ now ] != 0 ) {
      if ( l != r ) {
        st[ L( now ) ] += lazy[ now ];
        st[ R( now ) ] += lazy[ now ];
        lazy[ L( now ) ] += lazy[ now ];
        lazy[ R( now ) ] += lazy[ now ];
      }
      lazy[ now ] = 0;
    }
  }
  void Build( int now, int l, int r ) {
    if ( l == r ) {
      st[ now ] = arr[ l ];
      return;
    }
    build( L( now ), l, mid );
    build( R( now ), mid + 1, r );
    Pull( now );
  }
  void Update( int ql, int qr, int value, int now, int l, int r ) {
    if ( ql > qr || l > qr || r < ql )
      return;
    Push( now, l, r );
    if ( l == ql && qr == r ) {
      st[ now ] += value;
      lazy[ now ] += value;
      return;
    }
    if ( qr <= mid ) update( ql, qr, value, L( now ), l, mid );
    else if ( mid < ql ) update( ql, qr, value, R( now ), mid + 1, r );
    else {
      update( ql, mid, value, L( now ), l, mid );
      update( mid + 1, qr, value, R( now ), mid + 1, r );
    }
    Pull( now );
  }
  int query( int ql, int qr, int now, int l, int r ) {
    if ( ql > qr || l > qr || r < ql )
      return 0;
    Push( now, l, r );
    if ( l == ql && qr == r )
      return st[ now ];
    if ( qr <= mid )
      return query( ql, qr, L( now ), l, mid );
    else if ( mid < ql )
      return query( ql, qr, R( now ), mid + 1, r );
    else {
      int left = query( ql, mid, L( now ), l, mid );
      int right = query( mid + 1, qr, R( now ), mid + 1, r );
      int ans = max( left, right );
      return ans;
    }
  }
};
