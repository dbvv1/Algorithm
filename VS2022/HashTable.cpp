#include <vector>
#include <list>
#include <algorithm>


template<typename Key, typename Value>
class HashMap {
public:
    HashMap(size_t size = 8) : data(size), numElements(0), loadFactorThreshold(0.75) {}

    void put(const Key& key, const Value& value) 
    {
        if (1.0 * numElements / data.size() >= loadFactorThreshold) 
        {
            rehash();
        }
        size_t index = hashFunction(key);
        auto& pairs = data[index];
        auto pairIter = std::find_if(pairs.begin(), pairs.end(),
            [&](const std::pair<Key, Value>& pair) { return pair.first == key; });
        if (pairIter != pairs.end())
        {
            pairIter->second = value;
        }
        else 
        {
            pairs.push_back(std::make_pair(key, value));
            ++numElements;
        }
    }

    Value get(const Key& key)
    {
        size_t index = hashFunction(key);
        auto& pairs = data[index];
        auto pairIter = std::find_if(pairs.begin(), pairs.end(),
            [&](const std::pair<Key, Value>& pair) { return pair.first == key; });
        if (pairIter != pairs.end()) 
        {
            return pairIter->second;
        }
        else 
        {
            throw std::_Xruntime_error("Key not found");
        }
    }

private:
    std::vector<std::list<std::pair<Key, Value>>> data;
    size_t numElements;
    double loadFactorThreshold;

    size_t hashFunction(const Key& key) 
    {
        return key % data.size();
    }

    void rehash() 
    {
        auto oldData = std::move(data);
        data.resize(2 * data.size());
        numElements = 0;
        for (auto& pairs : oldData) 
        {
            for (auto& pair : pairs) 
            {
                put(pair.first, pair.second);
            }
        }
    }
};