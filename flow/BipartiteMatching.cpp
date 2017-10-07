// O( ( V + E ) * sqrt( V ) )
class BipartiteMatching {
  public:
    static const int N = 1e5 + 10; // total number of nodes, n + m
    static const int NIL = 0;
    static const int INF = ( 1 << 28 );
    vector< int > G[N];
    int n, m, match[N], dist[N];
    // n: number of nodes on left side, nodes are numbered 1 to n
    // m: number of nodes on right side, nodes are numbered n+1 to n+m
    // G = NIL[0] ∪ G1[G[1---n]] ∪ G2[G[n+1---n+m]]
    bool BFS() {
      int i, u, v, len;
      queue< int > Q;
      for(i=1; i<=n; i++) {
        if(match[i]==NIL) {
          dist[i] = 0;
          Q.push(i);
        }
        else dist[i] = INF;
      }
      dist[NIL] = INF;
      while(!Q.empty()) {
        u = Q.front(); Q.pop();
        if(u!=NIL) {
          len = G[u].size();
          for(i=0; i<len; i++) {
            v = G[u][i];
            if(dist[match[v]]==INF) {
              dist[match[v]] = dist[u] + 1;
              Q.push(match[v]);
            }
          }
        }
      }
      return (dist[NIL]!=INF);
    }
    bool DFS(int u) {
      int i, v, len;
      if(u!=NIL) {
        len = G[u].size();
        for(i=0; i<len; i++) {
          v = G[u][i];
          if(dist[match[v]]==dist[u]+1) {
            if(DFS(match[v])) {
              match[v] = u;
              match[u] = v;
              return true;
            }
          }
        }
        dist[u] = INF;
        return false;
      }
      return true;
    }
    int HopcroftKarp() {
      int matching = 0, i;
      // match[] is assumed NIL for all vertex in G
      while(BFS())
        for(i=1; i<=n; i++)
          if(match[i]==NIL && DFS(i))
            matching++;
      return matching;
    }
    void AddEdge( int u, int v ) {
      G[ u ].push_back( n + v );
    }
    int Solve() {
      return HopcroftKarp();
    }
};
