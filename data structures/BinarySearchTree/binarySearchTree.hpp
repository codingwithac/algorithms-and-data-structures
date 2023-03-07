#include "node.hpp"
#include <stdexcept>

using namespace std;

/**
 * A generic class implementing a binary search tree.
*/

template <typename Key, typename Value>
class BinarySearchTree
{
    // holds the number of nodes in the BST
    int nodes;

    // points to the root node of the BST
    Node<Key, Value> *root;

    // private method used internally to search for a given key and return its associated value
    Value get(Node<Key, Value> *node, Key key)
    {
        // base case: key is not in the BST (search miss)
        if (node == nullptr)
            throw runtime_error{"Error in get(): Key is not in the BST."};

        // case: given key is smaller than the current node's key
        if (key < node->getKey())
            // search the key in the left subtree
            return get(node->getLeft(), key);

        // case: given key is greater than the current node's key
        else if (key > node->getKey())
            // search the key in the right subtree
            return get(node->getRight(), key);

        // case: given key is found
        else
            // return the associated value
            return node->getValue();
    }

    // private method used to insert a key-value pair into the BST
    Node<Key, Value> *insert(Node<Key, Value> *node, Key key, Value value)
    {
        // base case: if we hit a leaf node, insert the key-value pair
        if (node == nullptr)
            return new Node<Key, Value>{key, value};

        // case: given key is smaller than the current node's key
        if (key < node->getKey())
        {
            // insert the key-value pair into the left subtree
            node->setLeftChild(insert(node->getLeft(), key, value));

            // increment the number of nodes
            this->nodes++;
        }

        // case: given key is larger than the current node's key
        else if (key > node->getKey())
        {
            // insert the key-value pair into the right subtree
            node->setRightChild(insert(node->getRight(), key, value));

            // increment the number of nodes
            this->nodes++;
        }

        // case: key already exists, we have to update its value (no incrementing of the nr. of node in the BST)
        else
            node->setValue(value);

        // finally return the current node
        return node;
    }

    // private method to get the node with the minimum key
    Node<Key, Value> *min(Node<Key, Value> *node)
    {
        // base case: if leaf node is hit, return it
        if (node->getLeft() == nullptr)
            return node;

        // recursive case: search the min node in the left subtree
        return min(node->getLeft());
    }

    // private method to get the node with the maximum key
    Node<Key, Value> *max(Node<Key, Value> *node)
    {
        // base case: if leaf node is hit, return it
        if (node->getRight() == nullptr)
            return node;

        // recursive case: search the max node in the right subtree
        return max(node->getRight());
    }

    // private method used to remove the node with the minimum key
    Node<Key, Value> *removeMin(Node<Key, Value> *node)
    {
        if (node->getLeft() == nullptr)
            return node->getRight();

        node->setLeftChild(removeMin(node->getLeft()));

        return node;
    }

    // private method to remove a key-value pair
    Node<Key, Value> *remove(Node<Key, Value> *node, Key key)
    {
        // base case: key is not in the BST
        if (node == nullptr)
            throw runtime_error{"Error in remove(): Key to be deleted is not in the BST."};

        // case: given key is smaller than the current node's key
        if (key < node->getKey())
            // delete the key-value pair in the left subtree
            node->setLeftChild(remove(node->getLeft(), key));
        // case: given key is greater than the current node's key
        else if (key > node->getKey())
            // delete the key-value pair in the right subtree
            node->setRightChild(remove(node->getRight(), key));

        // case: given key is found (search hit)
        else
        {
            // case: no child or right child
            if (node->getLeft() == nullptr)
                return node->getRight();

            // case: no child or left child
            if (node->getRight() == nullptr)
                return node->getLeft();

            // case: node to be deleted has two children

            // get a reference to the node to be deleted
            Node<Key, Value> *refNodeToDelete = node;

            // get a reference to the minimum node in the right subtree
            node = min(refNodeToDelete->getRight());

            // adjust the right child of the min node
            node->setRightChild(removeMin(refNodeToDelete->getRight()));

            // adjust the left child of the min node
            node->setLeftChild(refNodeToDelete->getLeft());
        }

        // return the node to the caller
        return node;
    }

public:
    // constructor
    BinarySearchTree() : nodes{0}
    {
        // empty tree; root points to null
        root = nullptr;
    }

    // used to get the number of nodes in the BST
    int getNodes() const
    {
        return this->nodes;
    }

    // used to check if BST is empty
    bool isEmpty() const
    {
        return this->nodes == 0 ? true : false;
    }

    // public method used to return the value associated with a key
    Value get(Key key)
    {
        // search the given key starting at the root
        return get(root, key);
    }

    // public method used to insert a key-value pair into a BST
    void insert(Key key, Value value)
    {
        // insert the given key-value pair starting at the root
        root = insert(root, key, value);
    }

    // public method used to get minimum key in the BST
    Key min()
    {
        // start searching from the root
        Node<Key, Value> *minimumNode = min(root);

        // return the key
        return minimumNode->getKey();
    }

    // public method used to get maximum key in the BST
    Key max()
    {
        // start searching from the root
        Node<Key, Value> *maximum = max(root);
        // return the key
        return maximum->getKey();
    }

    // public method used to delete a key-value pair
    void removal(Key key)
    {
        // start removing from the root
        root = remove(root, key);
    }
};