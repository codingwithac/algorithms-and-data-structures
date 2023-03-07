#include "binarySearchTree.hpp"
#include <iostream>
#include <string>

/**
 * Here, we just demonstrate the BinarySearchTree implementations.
*/

int main()
{
    // create a BinarySearchTree instance
    BinarySearchTree<int, string> *bst = new BinarySearchTree<int, string>{};

    try
    {
        // insert some key-value pairs
        bst->insert(10, "Kevin");
        bst->insert(65, "James");
        bst->insert(4, "Jane");

        // get some values
        cout << "Value of 10: " << bst->get(10) << endl;
        cout << "Value of 4: " << bst->get(4) << endl;
        cout << "Value of 65: " << bst->get(65) << endl;

        // check number of nodes
        cout << "Number of nodes in the BST: " << bst->getNodes() << endl;

        // check if BST is empty
        cout << "Is the BST empty? Answer: " << boolalpha << bst->isEmpty() << endl;

        // get the minimum key
        cout << "Minimum key: " << bst->min() << endl;

        // get the maximum key
        cout << "Maxiumum key: " << bst->max() << endl;

        // delete node with key 65
        bst->removal(65);

        // get the new maximum key
        cout << "Maxiumum key: " << bst->max() << endl;
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << endl;
    }
}
