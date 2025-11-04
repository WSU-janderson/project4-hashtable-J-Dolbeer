#include "HashTableBucket.h"

HashTableBucket::HashTableBucket() : key(""), value(0), type(BucketType::ESS) {}

HashTableBucket::HashTableBucket(const std::string& key, const size_t& value)
    : key(key), value(value), type(BucketType::NORMAL) {}

void HashTableBucket::load(const std::string& key, const size_t& value) {
    this->key = key;
    this->value = value;
    type = BucketType::NORMAL;
}

bool HashTableBucket::isEmpty() const {
    return type != BucketType::NORMAL;
}

bool HashTableBucket::isEmptySinceStart() const {
    return type == BucketType::ESS;
}

bool HashTableBucket::isEmptyAfterRemove() const {
    return type == BucketType::EAR;
}

void HashTableBucket::makeNormal() { type = BucketType::NORMAL; }
void HashTableBucket::makeESS() { type = BucketType::ESS; }
void HashTableBucket::makeEAR() { type = BucketType::EAR; }

const std::string& HashTableBucket::getKey() const { return key; }
size_t HashTableBucket::getValue() const { return value; }
void HashTableBucket::setValue(size_t val) { value = val; }

std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    if (bucket.type == BucketType::NORMAL)
        os << "{" << bucket.key << ": " << bucket.value << "}";
    else if (bucket.type == BucketType::EAR)
        os << "[EAR]";
    else
        os << "[ESS]";
    return os;
}
