/**
 * A program used to test the concrete implementation of the UnionFind API.
*/
#include "quick_find.hpp"

int main()
{

    QuickFind qf{10};

    qf.unify(4, 3);
    qf.unify(3, 8);

    qf.printId();

    cout << "Are 3 and 8 connected? Answer: " << boolalpha << qf.connected(3, 8) << endl;
    cout << "Are 1 and 2 connected? Answer: " << boolalpha << qf.connected(1, 2) << endl;

    cout << "Number of components: " << qf.getCount() << endl;
}