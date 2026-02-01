#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void myErase(ordered_set<int> &t, int v){
    int rank = t.order_of_key(v);
    ordered_set<int>::iterator it = t.find_by_order(rank);
    t.erase(it);
}