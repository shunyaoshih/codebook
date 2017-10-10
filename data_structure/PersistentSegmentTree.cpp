// tested with spoj MKTHNUM - K-th Number
#define mid ((l+r)>>1)
class Node {
  public:
    int value, l, r;
    Node() { value = l = r = 0; }
};
class SegmentTree {
  public:
    static const int N = 1e5 + 10;
    int ver_size, st_size;
    vector< int > ver;
    vector< Node > st;

    SegmentTree() {
      ver_size = st_size = 0;
      ver.resize( N );
      st.resize( 70 * N );
      ver[ ver_size++ ] = 1;
      st[ 0 ] = st[ 1 ] = Node(); st_size = 2;
    }
    void AddVersion() {
      ver[ ver_size++ ] = st_size++;
      st[ ver[ ver_size - 1 ] ] = st[ ver[ ver_size - 2 ] ];
    }
    inline void Pull( int now ) {
      int lchild = st[ now ].l, rchild = st[ now ].r;
      st[ now ].value = st[ lchild ].value + st[ rchild ].value;
    }
    void Build( int now = 1, int l = 1, int r = N ) {
      if ( l == r ) return;
      st[ now ].l = st_size++;
      st[ now ].r = st_size++;
      Build( st[ now ].l, l, mid );
      Build( st[ now ].r, mid + 1, r );
      Pull( now );
    }
    void Update( int prv_now, int now, int pos, int l = 1, int r = N ) {
      if ( l == r ) {
        st[ now ].value += 1;
        return;
      }
      if ( pos <= mid ) {
        st[ now ].l = st_size++;
        st[ st[ now ].l ] = st[ st[ prv_now ].l ];
        Update( st[ prv_now ].l, st[ now ].l, pos, l, mid );
      }
      else {
        st[ now ].r = st_size++;
        st[ st[ now ].r ] = st[ st[ prv_now ].r ];
        Update( st[ prv_now ].r, st[ now ].r, pos, mid + 1, r );
      }
      Pull( now );
    }
    pair< int, bool > Query( int prv_now, int now, int k, int l = 1, int r = N ) {
      int prv_value = st[ prv_now ].value, now_value = st[ now ].value;
      if ( l == r and now_value - prv_value == k )
        return make_pair( l, true );
      else if ( now_value - prv_value < k )
        return make_pair( now_value - prv_value, false );
      pair< int, bool > child = Query( st[ prv_now ].l, st[ now ].l, k, l, mid );
      if ( child.second == false ) {
        k -= st[ st[ now ].l ].value - st[ st[ prv_now ].l ].value;
        child = Query( st[ prv_now ].r, st[ now ].r, k, mid + 1, r );
      }
      return child;
    }
};
