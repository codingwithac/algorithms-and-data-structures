#include <vector>
#include <functional>
#include <iostream>
#include <exception>
#include "element.hpp"
using namespace std;

/**
 * The LinearProbing class contains the logic to apply modular hashing using linear probing 
 * (a method of open addressing) for collision resolution. Linear probing is a collision resolution 
 * strategy for handling the case when a hash table entry is already occupied. In that case, linear
 * probing just checks the next entry until an empty entry is found.
 * A hash function which converts keys into array indices is implemented in the 'hashing' method. 
 * The method 'put' is used to insert a key-value pair into the hash table and the method 'removal' is used
 * to delete a key-value pair from the hash table.
 * If we want to know the value of a key, we can use the 'getValue' method.
*/

template <typename Key, typename Value>
class LinearProbing
{
    // holds the number of key-value pairs
    int elements;

    // holds the size of the hash table
    int size;

    // our hash table
    vector<Element<Key, Value> *> hashTable;

    // our hasher which we'll use for hashing
    hash<Key> hasher;

    // used to resize the hashTable
    void resize(int newSize)
    {
        // set the new size of the hashTable
        this->size = newSize;

        // create a temporary hash table
        vector<Element<Key, Value> *> tmp;
        tmp.assign(newSize, nullptr);

        // scan through the hashTable
        for (const auto element : hashTable)
        {
            // if element exists
            if (element != nullptr)
            {
                // determine its hash code
                auto hashCode = hashing(element->getKey());

                // insert it into tmp
                tmp[hashCode] = element;
            }
        }

        // clear the hash table
        hashTable.clear();

        // swap the contents
        hashTable.swap(tmp);

        // clear tmp since it is not needed anymore
        tmp.clear();
    }

public:
    // constructor
    LinearProbing(int size) : elements{0}
    {
        // set the size of the hash table
        this->size = size;

        // default initialize the hash table
        this->hashTable.assign(this->size, nullptr);
    }

    // used to get the number of key-value pairs in the hash table
    int getElements() const
    {
        return this->elements;
    }

    // check if hash table is empty
    bool isEmpty() const
    {
        return this->elements == 0 ? true : false;
    }

    // used to apply modular hashing
    int hashing(Key key)
    {
        return hasher(key) % this->size;
    }

    // used to check if hashtable contains a given key
    bool contains(Key key)
    {
        // scan through the hash table
        for (auto i = hashing(key); hashTable[i] != nullptr; i = (i + 1) % this->size)
            // if key is found, return true
            if (hashTable[i]->getKey() == key)
                return true;

        // otherwise, return false
        return false;
    }

    // puts a key-value pair into the hash table
    void put(Key key, Value value)
    {
        // guarantees that the hash table is at most one-half full
        if (this->elements >= this->size / 2)
            resize(2 * this->size);

        // the index where we store our key-value pair or just update its value
        int i{};

        // apply linear probing to find an unoccupied location
        for (i = hashing(key); hashTable[i] != nullptr; i = (i + 1) % this->size)
        {
            // if key already in hashTable
            if (hashTable[i]->getKey() == key)
            {
                // update its value
                hashTable[i]->setValue(value);

                // and finish the linear probing
                return;
            }
        }

        // store the key-value pair to the unoccupied location
        hashTable[i] = new Element<Key, Value>{key, value};

        // increment nr. of elements
        this->elements++;
    }

    // used to delete a key-value pair
    void removal(Key key)
    {
        // no need to remove, when key does not exist
        if (!contains(key))
            return;

        // determine the hash code
        auto i = hashing(key);

        // scan through the hash table to find the index of the key-value pair to be deleted
        while (hashTable.at(i)->getKey() != key)
            i = (i + 1) % this->size;

        // delete the key-value pair at index 'i'
        hashTable[i] = nullptr;

        // now, we need to reinsert into the hash table all of the keys in the
        // cluster to the right of the deleted key
        i = (i + 1) % this->size;
        while (hashTable[i] != nullptr)
        {
            // save key and value for reinserting after deletion
            Key k = hashTable[i]->getKey();
            Value v = hashTable[i]->getValue();

            // delete
            hashTable[i] = nullptr;

            // decrement the nr of key value pairs
            this->elements--;

            // reinsert the element
            put(k, v);

            // go to next element in the cluster
            i = (i + 1) % this->size;
        }

        // decrement the nr of key-value pairs
        this->elements--;

        // guarantees that the hashTable is at least one-eight full
        if (this->elements > 0 && this->elements <= this->size / 8)
            resize(this->size / 2);
    }

    // used to get the value of a given key
    Value getValue(Key key)
    {
        for (auto i = hashing(key); hashTable[i] != nullptr; i = (i + 1) % this->size)
            // if given key is found in hashtable, return its value
            if (hashTable[i]->getKey() == key)
                return hashTable[i]->getValue();

        // if key-value pair is not in hashTable, an exception is thrown
        throw runtime_error{"No value: key-value pair not exists."};
    }

    // used to print the hash table content (only for debugging purposes)
    void printHashTable()
    {
        int index{};
        for (const auto element : hashTable)
        {
            cout << "Index " << index << ": ";
            if (element != nullptr)
                cout << "(" << element->getKey() << "," << element->getValue() << ")" << endl;

            else
                cout << "unoccupied" << endl;

            index++;
        }
    }
};