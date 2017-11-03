/***************PB_DS priority_queue*****************/
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
typedef priority_queue<T,less<T>,pairing_heap_tag> PQ;
typedef PQ::point_iterator PQit;
point_iterator push(const_reference key)
void modify(point_iterator it, const_reference key)
void erase(point_iterator it)
T top() 
void pop() 
point_iterator begin() 
point_iterator end() 
void join(priority_queue &other) 
template<class Pred> void split(Pred prd, priority_queue &other) //Other will contain only values v for which prd(v) is true. When calling this method, other's policies must be equivalent to this object's policies.
template<class Pred> size_type erase_if(Pred prd) //Erases any value satisfying prd; returns the number of value erased.
//1. push will return a point_iterator, which can be saved in a vector and modify or erase afterward.
//2. using begin() and end() can traverse all elements in the priority_queue.
//3. after join, other will be cleared.
//4. for optimizing Dijkstra, use pairing_heap
//5. binary_heap_tag is better that std::priority_queue
//6. pairing_heap_tag is better than binomial_heap_tag and rc_binomial_heap_tag
//7. when using only push, pop and join, use binary_heap_tag
//8. when using modify, use pairing_heap_tag or thin_heap_tag
/*******************PB_DS tree***********************/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
typedef tree<K, T, less<K>, rb_tree_tag, Node_Update> TREE;
//similar to std::map
//when T = __gnu_pbds::null_type, become std::set
//when Node_Update = tree_order_statistics_node_update, TREE become a ordered TREE with two new functions:
//1. iterator find_by_order(size_type order) return the smallest order-th element(e.x. when order = 0, return the smallest element), when order > TREE.size(), return end()
//2. size_type order_of_key(const_reference key) return number of elements smaller than key
void join(tree &other) //other和*this的值域不能相交
void split(const_reference key, tree &other) // 清空 other, 然後把*this當中所有大於key的元素移到other
//自定義Node_Update : 查詢子段和的map<int, int>，需要紀錄子樹的mapped_value的和。
template<class Node_CItr, class Node_Itr, class Cmp_Fn, class _Alloc>
struct my_nd_upd {
  virtual Node_CItr node_begin () const = 0;
  virtual Node_CItr node_end () const = 0;
  typedef int metadata_type ; //額外信息，這邊用int
  inline void operator()(Node_Itr it,Node_CItr end_it){
    Node_Itr l=it.get_l_child(), r=it.get_r_child();
    int left = 0 , right = 0;
    if(l != end_it) left = l.get_metadata();
    if(r != end_it) right = r.get_metadata();
    const_cast<metadata_type&>(it.get_metadata())=
      left+right+(*it)->second;
  } 
  //operator()功能是將節點it的信息更新，end_it表空節點
  //it是Node_Itr, *之後變成iterator, 再取->second變節點的mapped_value
  inline int prefix_sum (int x) {
    int ans = 0;
    Node_CItr it = node_begin();
    while(it!=node_end()){
      Node_CItr l = it.get_l_child() , r = it.get_r_child();
      if(Cmp_Fn()(x , (*it)->first)) it = l;
      else {
        ans += (*it)->second;
        if(l != node_end ()) ans += l.get_metadata();
        it = r;
      }
    }
    return ans;
  }
  inline int interval_sum(int l ,int r) 
  {return prefix_sum(r)-prefix_sum(l-1);}
};
tree<int, int, less<int>, rb_tree_tag, my_nd_upd> T;
printf("%d\n", T.interval_sum(a, b));
/*******************PB_DS hash*********************/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
__gnu_pbds::cc_hash_table<Key, Mapped>
__gnu_pbds::gp_hash_table<Key, Mapped>
//支援find和operator[]
/*******************PB_DS trie*********************/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>
typedef trie<string, null_type, trie_string_access_traits<>, pat_trie_tag,
             trie_prefix_search_node_update> pref_trie;
pref_trie.insert(const string &str);
auto range = pref_trie.prefix_range(const string &str);
for(auto it = range.first; it != range.second; ++it)
  cout << *it << '\n';
