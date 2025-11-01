#pragma once
#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <iostream>
#include "HashTableBucket.h"

class HashTable {
    private:
    std::vector<std::weak_ptr<HashTableBucket>> tableData;
    std::vector<size_t> offsets;
    size_t numElements;
    size_t capacity_;

    void generateOffsets();
    size_t hash(const std::string& key) const;
    void resize();
    void rehashBackwards();
    void debugDumpToJSON() const;

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

    friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);
};