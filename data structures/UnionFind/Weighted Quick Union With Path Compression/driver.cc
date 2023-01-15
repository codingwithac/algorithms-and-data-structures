/**
 * A program used to test the concrete implementation of the UnionFind API.
*/
#include "weighted_quick_union_with_path_compression.hpp"

int main()
{

    WeightedQuickUnionWithPathCompression wqu{10};

    wqu.unify(4, 3);
    wqu.unify(3, 8);

    wqu.printId();

    cout << "Are 3 and 8 connected? Answer: " << boolalpha << wqu.connected(3, 8) << endl;
    cout << "Are 1 and 2 connected? Answer: " << boolalpha << wqu.connected(1, 2) << endl;

    cout << "Number of components: " << wqu.getCount() << endl;
}