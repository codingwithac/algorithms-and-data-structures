/**
 * A program illustrating the weighted quick-union with path compression. 
*/
#include "union_find.hpp"

class WeightedQuickUnionWithPathCompression : public UnionFind
{
    // a structure used to keep track of the size of each component
    vector<int> compSz;

public:
    WeightedQuickUnionWithPathCompression(int n) : UnionFind{n}
    {

        // initialize the size of each component
        // at the beginning each component has the size 1
        for (int i{}; i < n; i++)
            compSz.push_back(1);
    }

    // concrete implementation of the virtual method find()
    int find(int p) override
    {
        int root = p;

        // loop until root of p is reached
        while (root != id[root])
            root = id[root];

        // apply "path compression"; all elements along the way point to their root
        while (root != p)
        {
            int successor = id[p];
            id[p] = root;
            p = successor;
        }

        return root;
    }

    // concrete implementation of the virtual method find()
    void unify(int p, int q) override
    {
        // get the root of p & q
        int root1 = find(p);
        int root2 = find(q);

        // if p & q are in the same component, there is nothing to do
        if (root1 == root2)
            return;

        // smaller root points to larger one
        if (compSz[root1] < compSz[root2])
        {
            id[root1] = root2;
            compSz[root2] += compSz[root1];
        }
        else
        {
            id[root2] = root1;
            compSz[root1] += compSz[root2];
        }

        // decrement number of components by 1
        count--;
    }
};