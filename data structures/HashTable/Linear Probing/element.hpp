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

    void setValue(Value newValue)
    {
        this->value = newValue;
    }

private:
    Key key;
    Value value;
};