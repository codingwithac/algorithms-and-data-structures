
/**
 * A generic class representing the node of a BST. 
 * It stores the key-value pair that gets inserted into the BST.
 * Every node has two pointers; one points to its left child, another points to its right child
*/
template <typename Key, typename Value>
class Node
{
    // used to hold the key
    Key key;
    // used to holds the value
    Value value;

    // pointer to the left child
    Node<Key, Value> *left;
    // pointer to the right child
    Node<Key, Value> *right;

public:
    // constructor
    Node(Key key, Value value) : key{key}, value{value}
    {
        // set both pointers to null
        left = right = nullptr;
    }

    // used to retrieve the key of this node
    Key getKey() const
    {
        return this->key;
    }

    // used to retrieve the value of this node
    Value getValue() const
    {
        return this->value;
    }

    // used to set the value of this node
    void setValue(Value newValue)
    {
        this->value = newValue;
    }

    // used to get the left child of this node
    Node<Key, Value> *getLeft() const
    {
        return this->left;
    }

    // used to get the right child of this node
    Node<Key, Value> *getRight() const
    {
        return this->right;
    }

    // used to set the left child of this node
    void setLeftChild(Node<Key, Value> *newLeftChild)
    {
        this->left = newLeftChild;
    }

    // used to set the right child of this node
    void setRightChild(Node<Key, Value> *newRightChild)
    {
        this->right = newRightChild;
    }
};