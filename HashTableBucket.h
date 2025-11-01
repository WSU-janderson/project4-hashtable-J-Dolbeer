#pragma once
#include <string>
#include <iostream>

enum class BucketType { NORMAL, ESS, EAR };

class HashTableBucket {
    private:
    std::string key;
    size_t value;
    BucketType type;

    public:
    HashTableBucket();
    HashTableBucket(const std::string& key, const size_t& value);

    void load(const std::string& key, const size_t& value);
    bool isEmpty() const;
    bool isEmptySinceStart() const;
    bool isEmptyAfterRemove() const;

    void makeNormal();
    void makeESS();
    void makeEAR();

    const std::string& getKey() const;
    size_t getValue() const;
    void setValue(size_t val);

    friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);
};