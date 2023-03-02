
/**
 * The SeparateChaining class contains the logic to apply modular hashing using separate chaining for 
 * collision resolution. Separate chaining is a collision resolution is a strategy for handling the case
 * when two or more keys to be inserted hash to the same array index. If that happens, they are stored in 
 * the same linked list.
 * Therefore, SeparateChaining has a vector 'hashTable' that stores a list of items of type 'Element'. 
 * A hash function which converts keys into array indices is implemented in the 'hashing' method. 
 * The method 'put' is used to insert a key-value pair into the hash table and the method 'removal' is used
 * to delete a key-value pair from the hash table.
 * If we want to know the value of a key, we can use the 'getValue' method.
 * 
*/

#include <vector>
#include <list>
#include <iostream>
#include <functional>
#include <exception>
#include "element.hpp"
using namespace std;

template <typename Key, typename Value>
class SeparateChaining
{
    int elements; // holds the number of key-value pairs
    int size;     // size of the hash table

    // declare our hash table
    vector<list<Element<Key, Value>>> hashTable;

    // our hasher which we'll use for hashing
    hash<Key> hasher;

    // used to resize the hashTable
    void resize(int newSize)
    {
        // change the size of the hashTable
        this->size = newSize;

        // create a temporary hash table
        vector<list<Element<Key, Value>>> tmp;

        // initialize tmp with empty linked lists
        tmp.assign(newSize, {});

        // scan through the hashTable
        for (int i = 0; i < hashTable.size(); i++)
        {
            // if current linked list is not empty
            if (!hashTable.at(i).empty())
            {
                // then scan through the linked list
                for (const auto element : hashTable.at(i))
                {
                    // determine the hash code
                    auto hashCode = hashing(element.getKey());

                    // insert the element in 'tmp'
                    tmp[hashCode].push_front(element);
                }

                // clear the linked list
                hashTable.at(i).clear();
            }
        }

        // now resize the hashTable
        hashTable.resize(newSize, {});

        // exchange each element of hashTable with those of 'tmp'
        hashTable.swap(tmp);

        // clear 'tmp'
        tmp.clear();
    }

public:
    // constructor
    SeparateChaining(int size) : elements{0}
    {
        // set the size of the hash table
        this->size = size;

        // fill the vector with empty lists
        for (int i = 0; i < this->size; i++)
            hashTable.push_back({});
    }

    // returns the size of the hashTable
    int getSize() const
    {
        return this->size;
    }

    // return number of elements in the hash table
    int getNrOfElements() const
    {
        return this->elements;
    }

    // check whether hash table is empty
    bool isEmpty() const
    {
        return this->elements == 0 ? true : false;
    }

    // define the hash function
    int hashing(Key key) const
    {
        // apply modular hashing
        return (hasher(key)) % size;
    }

    // checks whether or not the key-value pair is in the hash table
    bool contains(Key key)
    {
        // determine the hash code so that we know where to look at
        auto hashCode = hashing(key);

        // start at the beginning of the linked list
        auto iter = hashTable.at(hashCode).begin();

        // scan through the linked list
        while (iter != hashTable.at(hashCode).end())
        {
            // is key already in the hash table ? if yes, return true
            if ((*iter).getKey() == key)
                return true;

            // go to next element
            iter++;
        }

        // otherwise return false
        return false;
    }

    // returns the value of a key
    Value getValue(Key key)
    {
        // check if key is in the hash table
        if (!contains(key))
            throw runtime_error{"No value: key-value pair does not exist."};

        // determine the hash code
        auto hashCode = hashing(key);

        // start at the begining of the linked list
        auto iter = hashTable.at(hashCode).begin();

        // search the key-value pair within the linked list at 'hashCode' in hashTable
        while (iter != hashTable.at(hashCode).end())
        {
            // key-value pair is found
            if ((*iter).getKey() == key)
                break;

            // go to next element
            iter++;
        }

        // if key is not found, throw an exception
        if (iter == hashTable.at(hashCode).end())
            throw runtime_error{"No value: key-value pair does not exist."};

        // otherwise, return the value
        return (*iter).getValue();
    }

    void put(Key key, Value value)
    {
        // guarantees that the hash table is at most one-half full
        if (this->elements >= this->size / 2)
            resize(2 * this->size);

        // determine the hash code
        auto hashCode = hashing(key);

        // create the new key-value pair
        auto keyValuePair = Element<Key, Value>{key, value};

        // add the key-value pair to the linked list located at 'hashCode' in hashTable
        hashTable.at(hashCode).push_front(keyValuePair);

        // increment nr. of key-value pairs
        this->elements++;
    }

    // used to delete a key-value pair
    void removal(Key key)
    {
        // check whether key exists
        if (!contains(key))
            throw runtime_error{"Removal failed: Key does not exist."};

        // determine the hash code
        auto hashCode = hashing(key);

        // remove if key of element equals given key
        hashTable.at(hashCode).remove_if([key](Element<Key, Value> element) { return element.getKey() == key; });

        // decrement nr of key-value pairs
        this->elements--;

        // guarantees that the hashTable is at least one-eight full
        if (this->elements > 0 && this->elements <= this->size / 8)
            resize(this->size / 2);
    }

    // print hashTable content (just for debugging purposes)
    void printHashTable()
    {
        int index = 0;
        for (const auto list : hashTable)
        {
            cout << "List " << index << ": ";
            for (const auto element : list)
                cout << "(" << element.getKey() << "," << element.getValue() << ") ";
            cout << endl;
            index++;
        }
    }
};
