vector<int> g[N];
int dep[N], low[N], stmp;
void go(int now, int prt){
  dep[now]=low[now]=++stmp;
  for( int son : g[now] ){
    if( son == prt ) continue;
    if( dep[son] ){
      low[now]=min(low[now], dep[son]);
      return;
    }
    go(son, now);
    low[now]=min(low[now], low[son]);
    if(dep[now] >= low[son])
      djs.uni(now, son);
    else
      // (now, son) is a bridge
  }
}
void solve(){
  stmp = 0;
  for( int i = 1 ; i <= n ; i ++ )
    dep[ i ] = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( dep[i] == 0 )
      go( i , i );
}
