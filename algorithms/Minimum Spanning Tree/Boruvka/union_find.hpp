#include <vector>
#include <iostream>
using namespace std;

/**
 * A program illustrating the interface of the UnionFind 
 * data structure. 
*/
class UnionFind
{
    // public member representing the components
    // e.g. id[i] = component id to which i belongs to
    vector<int> id;

    // public member holding the number of components
    int count;

    // a structure used to keep track of the size of each component
    vector<int> compSz;

public:
    // constructor to initialize n elements with integer names
    UnionFind(int n) : count{n}
    {
        // initialize the component id structure
        for (int i{}; i < n; i++)
            id.push_back(i);

        // initialize the compSize vector; each component has size 1
        for (int i{}; i < n; i++)
            compSz.push_back(1);
    }

    // method to add connection between p and q
    // so, it merges two components if the two elements p & q are in different components
    // after merge is done, it also decrements the number of components stored in
    // 'count' by 1
    void unify(int p, int q)
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

    // method to find the component id of p
    // so, returns an integer component id for a given element p
    int find(int p)
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

    // method to check if p & q are in the same component
    bool connected(int p, int q)
    {
        return find(p) == find(q);
    }

    // method to return the number of components
    int getCount()
    {
        return count;
    }

    // public method to print the component id structure to the console
    // (for debugging purposes)
    void printId()
    {
        for (int i{}; i < id.size(); i++)
            cout << "Component id of " << i << " is: " << id[i] << endl;
    }
};