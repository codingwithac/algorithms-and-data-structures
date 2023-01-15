/**
 * A program used to test the concrete implementation of the UnionFind API.
*/
#include "quick_union.hpp"

int main()
{

    QuickUnion qu{10};

    qu.unify(4, 3);
    qu.unify(3, 8);

    qu.printId();

    cout << "Are 3 and 8 connected? Answer: " << boolalpha << qu.connected(3, 8) << endl;
    cout << "Are 1 and 2 connected? Answer: " << boolalpha << qu.connected(1, 2) << endl;

    cout << "Number of components: " << qu.getCount() << endl;
}