// CODE

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

using Key = string;           // Any type
using Comparator = less<Key>; // Any compare function

using os_tree = tree<Key, null_type, Comparator, rb_tree_tag,
                     tree_order_statistics_node_update>;

// USAGE

int main() {
  os_tree t;

  // Same as `set`: insert, find etc' plus:

  // Get the i-th largest element in O(lg n).
  // i.e. 0 gets the smallest element, n-1 get's the largest.
  t.find_by_order(i);

  // Get the order of this key in O(lg n).
  // i.e. if returns 5, than `"key"` is bigger than 5 other keys.
  t.order_of_key("key");
}
