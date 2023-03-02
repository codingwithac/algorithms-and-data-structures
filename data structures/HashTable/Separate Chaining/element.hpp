/**
 * The struct 'Element' represents a key-value pair which we will use in the 
 * SeparateChaining class to store key-value pairs within a hash table.
*/

template <typename Key, typename Value>
struct Element
{
    Element(Key key, Value value)
    {
        this->key = key;
        this->value = value;
    }

    Key getKey() const
    {
        return this->key;
    }

    Value getValue() const
    {
        return this->value;
    }

private:
    Key key;
    Value value;
};