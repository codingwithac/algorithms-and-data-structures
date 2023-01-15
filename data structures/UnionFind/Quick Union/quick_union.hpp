/**
 * A program illustrating the quick-union method. 
*/
#include "union_find.hpp"

class QuickUnion : public UnionFind
{
public:
    QuickUnion(int n) : UnionFind{n} {}

    // concrete implementation of the virtual method find()
    int find(int p) override
    {
        // loop until root is reached
        while (p != id[p])
            p = id[p];

        return p;
    }

    // concrete implementation of the virtual method unify()
    void unify(int p, int q) override
    {
        // get the root of p & q
        int root1 = find(p);
        int root2 = find(q);

        // if p & q are in the same component, there is nothing to do
        if (root1 == root2)
            return;

        // root of p points to root of q
        id[root1] = root2;

        // decrement the number of components by 1
        count--;
    }
};