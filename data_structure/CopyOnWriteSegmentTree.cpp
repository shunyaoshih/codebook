// tested with ASC 29 B
#define mid ( ( l + r ) >> 1 )
class Node {
 public:
  int value, l, r, who;
  Node() {}
  Node( int _v ) : value( _v ) { l = r = who = 0; }
};
class SegmentTree {
 public:
  static const int N = 1e9;
  vector< Node > st;

  inline void Pull( int now ) {
    int lchild = st[ now ].l;
    int rchild = st[ now ].r;
    if ( lchild != 0 ) {
      st[ now ].value = st[ lchild ].value;
      st[ now ].who = st[ lchild ].who;
    }
    if ( rchild != 0 && st[ rchild ].value > st[ now ].value ) {
      st[ now ].value = st[ rchild ].value;
      st[ now ].who = st[ rchild ].who;
    }
  }
  void Build() {
    st.push_back( Node() );  // Null Node
    st.push_back( Node( 0 ) );
  }
  void Update( int ql, int qr, int value, int who, int now = 1, int l = 1, int r = N ) {
    if ( ql > qr or qr < l or ql > r ) return;
    if ( l == ql && qr == r ) {
      st[ now ].value = value;
      st[ now ].who = who;
      return;
    }
    if ( qr <= mid ) {
      if ( st[ now ].l == 0 ) {
        st[ now ].l = st.size();
        st.push_back( Node( 0 ) );
      }
      Update( ql, qr, value, who, st[ now ].l, l, mid );
    }
    else if ( mid < ql ) {
      if ( st[ now ].r == 0 ) {
        st[ now ].r = st.size();
        st.push_back( Node( 0 ) );
      }
      Update( ql, qr, value, who, st[ now ].r, mid + 1, r );
    }
    else {
      if ( st[ now ].l == 0 ) {
        st[ now ].l = st.size();
        st.push_back( Node( 0 ) );
      }
      if ( st[ now ].r == 0 ) {
        st[ now ].r = st.size();
        st.push_back( Node( 0 ) );
      }
      Update( ql, mid, value, who, st[ now ].l, l, mid );
      Update( mid + 1, qr, value, who, st[ now ].r, mid + 1, r );
    }
    Pull( now );
  }
  pair< int, int > Query( int ql, int qr, int now = 1, int l = 1, int r = N ) {
    if ( ql > qr or qr < l or ql > r ) return { 0, 0 };
    if ( l == ql && qr == r ) {
      return { st[ now ].value, st[ now ].who };
    }
    if ( qr <= mid ) {
      if ( st[ now ].l == 0 ) return { 0, 0 };
      return Query( ql, qr, st[ now ].l, l, mid );
    }
    else if ( mid < ql ) {
      if ( st[ now ].r == 0 ) return { 0, 0 };
      return Query( ql, qr, st[ now ].r, mid + 1, r );
    }
    else {
      pair< int, int > lchild = { 0, 0 };
      if ( st[ now ].l != 0 ) lchild = Query( ql, mid, st[ now ].l, l, mid );
      pair< int, int > rchild = { 0, 0 };
      if ( st[ now ].r != 0 ) rchild = Query( mid + 1, qr, st[ now ].r, mid + 1, r );
      pair< int, int > ans = { 0, 0 };
      if ( lchild.first > ans.first ) {
        ans.first = lchild.first;
        ans.second = lchild.second;
      }
      if ( rchild.first > ans.first ) {
        ans.first = rchild.first;
        ans.second = rchild.second;
      }
      return ans;
    }
  }
};
