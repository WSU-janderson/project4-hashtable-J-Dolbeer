#pragma once
#include "HashTableBucket.h"
#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <ostream>
#include <random>

class HashTable {
private:
    std::vector<std::weak_ptr<HashTableBucket>> table;
    std::vector<size_t> offsets;
    size_t numItems;

    void generateOffsets();
    size_t hash(const std::string& key) const;
    void resizeIfNeeded();
    void rehashAll(const std::vector<std::shared_ptr<HashTableBucket>>& oldTable);

public:
    HashTable(size_t initCapacity = 8);

    bool insert(const std::string& key, const size_t& value);
    bool remove(const std::string& key);
    bool contains(const std::string& key) const;
    std::optional<size_t> get(const std::string& key) const;
    size_t& operator[](const std::string& key);
    std::vector<std::string> keys() const;
    double alpha() const;
    size_t capacity() const;
    size_t size() const;
    void rehashBackwards();
    
    friend std::ostream& operator<<(std::ostream& os, const HashTable& ht);
};
