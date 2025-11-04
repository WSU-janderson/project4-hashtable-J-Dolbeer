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
    static constexpr const char* SENTINEL_KEY = "SENTINEL_KEY_42";

    HashTableBucket() : key(SENTINEL_KEY), value(0), type(BucketType::ESS) {}
    HashTableBucket(const std::string& k, const size_t& v) : key(k), value(v), type(BucketType::NORMAL) {}

    void load(const std::string& k, const size_t& v) {
        key = k;
        value = v;
        type = BucketType::NORMAL;
    }

    bool isEmpty() const {
        return type != BucketType::NORMAL;
    }

    bool isESS() const { return type == BucketType::ESS; }
    bool isEAR() const { return type == BucketType::EAR; }
    void makeEAR() { type = BucketType::EAR; key = SENTINEL_KEY; }
    void makeESS() { type = BucketType::ESS; key = SENTINEL_KEY; }

    const std::string& getKey() const { return key; }
    size_t& getValue() { return value; }
    const size_t& getValue() const { return value; }

    friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& b) {
        if (b.type == BucketType::NORMAL) os << "<" << b.key << ", " << b.value << ">";
        return os;
    }
};
