/**
 * A program illustrating the quick-find method. 
*/
#include "union_find.hpp"

class QuickFind : public UnionFind
{
public:
    QuickFind(int n) : UnionFind{n} {}

    // concrete implementation of the virtual method find()
    int find(int p) override
    {
        // return the component id to which the element p belongs to
        return id[p];
    }

    // concrete implementation of the virtual method unify()
    void unify(int p, int q) override
    {
        // get compoenent id of p & q
        int compIdOne = find(p);
        int compIdTwo = find(q);

        // if both elements are in the same component, there is nothing to do
        if (compIdOne == compIdTwo)
            return;

        // scan through the component id structure & update the ids
        for (int i{}; i < id.size(); i++)
            if (id[i] == compIdOne)
                id[i] = compIdTwo;

        // decrement the number of components by 1
        count--;
    }
};